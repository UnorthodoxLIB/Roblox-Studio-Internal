#include "patcherlib.c"

int main()
{
	updatePatcherData();
	printf("PATCHING!\n");
	PatchStudio("RobloxStudioBeta.exe", "RobloxStudioInternal.exe");
}