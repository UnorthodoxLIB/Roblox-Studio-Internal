#include "patcherlib.c"

int main()
{
	char cerr = 0;

	printf(_);
	printf("\n10 of each, signatures & cooresponding patches will be downloaded.\nPress enter if you agree.")
	getchar();
	printf("\n\nGetting sigs & cooresponding patches.\n");
	updatePatcherData();
	printf("Successfully retreived Sigs & cooresponding patches.\n\nPatching");

	char Success = PatchStudio("RobloxStudioBeta.exe", "RobloxStudioInternal.exe");

	switch(Success)
	{
		case 0:
			printf("Successfully patched RobloxStudioInternal.exe!")
			goto finish;
		case 1:
			printf("Please place the executable in the same directory as RobloxStudioBeta.exe!")
			cerr=1;
			goto error;
		case 2:
			printf("An error occured initializing RobloxStudioInternal.exe, try re-running the executable.\nIf this message still appears, try running it as administrator!");
			cerr=2;
			goto error;
		default:
			printf("An unknown error occured.")
			cerr=3
			goto error;
	}
error:
	printf("An error occured & Studio probably wasn't patched.\nFor help, visit https://github.com/unorthodoxlib/roblox-studio-internal-patcher\nPress enter to close this window.\n")
	return cerr;
finish:
	printf("Press enter to close.")
	getchar();
	return cerr;
}