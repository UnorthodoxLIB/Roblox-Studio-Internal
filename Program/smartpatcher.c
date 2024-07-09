#include "patcherlib.c"

int main()
{
	printf(_);
	printf("\nWARNING, This version *is not really too smart*\nall it does is automatically update Sigs & their coresponding patch.\n\nPress enter if you agree & wish to proceed.");
	getchar();
	printf("\nUpdating Sigs, & Patchcodes\n");
	updatePatcherData();
	printf("Successfully updated Sigs & Patchcodes, Creating studio internal.\nFinding & Patching Roblox Studio\n");
	unsigned __int8 Success = PatchStudio("RobloxStudioBeta.exe", "RobloxStudioInternal.exe");

	if (Success == 0)
		printf("Created Roblox Studio Internal\n");
	else if (Success == 1)
		printf("Place this executable in the same directory as RobloxStudioBeta.exe! If it is there, feel free to ask for help on the Github.\nhttps://github.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher\n");
	else if (Success == 2)
		printf("For whatever reason, RobloxStudioInternal.exe wasn't able to initialize!\n For help, feel free to post on github.\nhttps://github.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher\n");
	else
		printf("An unknown error occured! Please report this to the github.\nhttps://github.com/UnorthodoxLIB/Roblox-Studio-Internal-Patcher\n");
	printf("Press enter to close.\n");
	getchar();
}