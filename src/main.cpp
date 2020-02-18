#include "Tracer.h"
#include <assert.h>
#include <time.h>
int main()
{
	clock_t tStart = clock();

	Tracer App;
	App.Initialise();
	int Code = App.Render();
	assert(Code == 1);
	clock_t tDelta = clock() - tStart;
	if (Code == 1) 	printf("Image render successful\n Time taken: %.2fs\n", (double)tDelta / CLOCKS_PER_SEC);
	else printf("ERROR %i - Image could not be produced\n", Code);

}