#include "patcherlib.h"

int main()
{
	static char cerr = 0;

	printf("Copyright (c) 2024 UnorthodoxLIB\n"
    "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
    "of this software and associated documentation files (the \"Software\"), to deal\n"
    "in the Software without restriction, including without limitation the rights\n"
    "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
    "copies of the Software, and to permit persons to whom the Software is\n"
    "furnished to do so, subject to the following conditions:\n\n"
    "The above copyright notice and this permission notice shall be included in all\n"
    "copies or substantial portions of the Software.\n\n"
    "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
    "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
    "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
    "SOFTWARE.\n"
);
	printf("\n10 of each, signatures & cooresponding patches will be downloaded.\nPress enter if you agree.");
	getchar();
	printf("\n\nGetting sigs & cooresponding patches.\n");
	updatePatcherData();
	printf("Successfully retreived Sigs & cooresponding patches.\n\nPatching");

	char Success = PatchStudio("RobloxStudioBeta.exe", "RobloxStudioInternal.exe");

	switch(Success)
	{
		case 0:
			printf("Successfully patched RobloxStudioInternal.exe!");
			goto finish;
		case 1:
			printf("Please place the executable in the same directory as RobloxStudioBeta.exe!");
			cerr=1;
			goto error;
		case 2:
			printf("An error occured initializing RobloxStudioInternal.exe, try re-running the executable.\nIf this message still appears, try running it as administrator!");
			cerr=2;
			goto error;
		default:
			printf("An unknown error occured.");
			cerr=3;
			goto error;
	}
error:
	printf("An error occured & Studio probably wasn't patched.\nFor help, visit https://github.com/unorthodoxlib/roblox-studio-internal-patcher\nPress enter to close this window.\n");
	getchar();
	return cerr;
finish:
	printf("Press enter to close.");
	getchar();
	return cerr;
}