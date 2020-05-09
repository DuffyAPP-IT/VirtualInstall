//DuffyAPP_IT 03/04/2020 - Contact james@it.duffy.app




#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//concat code used for constructing system call..
char *concatenate(const char *a, const char *b, const char *c) {
	size_t alen = strlen(a);
	size_t blen = strlen(b);
	size_t clen = strlen(c);
	char *res = malloc(alen + blen + clen + 1);
	if (res) {
		memcpy(res, a, alen);
		memcpy(res + alen, b, blen);
		memcpy(res + alen + blen, c, clen + 1);
	}
	return res;
}


int main() {
//Basic init & notice..
	system("clear");
	printf("-----------------------\n");
	printf ("DuffyAPP_IT - Welcome To VirtualInstall - Release 1\n");
	printf("-----------------------\n");
	printf("Ensure 'rootfsin.dmg' is in the current working directory of the application and \nthat you have executed this from the terminal, and not by double clicking the binary..\n\n");
	printf("The current working directory is:\n");
	system("pwd");
	printf("\nRunning..\n");
	sleep(3);
	system("asr -source rootfsin.dmg -target rootfsout.dmg --embed -erase -noprompt --chunkchecksum --puppetstrings");
	printf("Complete - Clean rootfsin.dmg? (0/1)\n");
	int opt;
	scanf("%d", &opt);
	switch(opt){
		case 0:
			printf("Skipping Process..\n");
			break;
		case 1:
			printf("Cleaning rootfsin.dmg..\n");
			system("rm rootfsin.dmg");
			printf("Stock DMG Prepared...\n");
			break;
		default:
			printf("Didn't understand your response.. Skipping Process..\n");
			break;
	}
	
		char * invapfs1 = "sudo /System/Library/Filesystems/apfs.fs/Contents/Resources/apfs_invert -d ";
		char invapfs2[15]; //User input
		char * invapfs3 = " -s 1 -n rootfsout.dmg";
		printf("Starting VirtualInstall...");
		sleep(4);
		printf("Creating Virtual APFS Disk\n");
		system("hdiutil create -size 10GB -fs APFS -volname iOS iOS.dmg  >/dev/null 2>&1");
		printf("\nCreated\n");
		
		sleep(1);
		printf("Attaching VDisk\n");
		system("hdiutil attach iOS.dmg");
		
		printf("Enter Disk identifier of */Volumes/iOS* in the form /dev/disk9s2 from the output above: ");
		scanf("%s", &invapfs2);
		char * invapfscom = concatenate(invapfs1, &invapfs2, invapfs3);
		printf("\nWaiting For Connection To Disk...\n");
		
		//wait for disk to mount, sometimes takes a few secs..
		sleep(8);
		printf("Connected\n");
		sleep(1);
		printf("Moving iOS RootFS\n");
		//copy prepared dmg to root of new apfs disk.
		system("cp rootfsout.dmg /Volumes/iOS/rootfsout.dmg  >/dev/null 2>&1");
		printf("\ncmd complete\n");

		//new code. prompts to remove rootfsout.dmg as it's no longer necessarry.

		printf("Clean rootfsout.dmg? (0/1)\n");
		int opt2;
		scanf("%d", &opt2);
		switch(opt2){
			case 0:
				printf("Skipping Process..\n");
				break;
			case 1:
				printf("Cleaning rootfsout.dmg..\n");
				system("rm rootfsout.dmg");
				printf("Old Rootfsout has been removed!\n");
				sleep(3);
				break;
			default:
				printf("Didn't understand your response.. Skipping Process..\n");
				break;
		}

		//End of new code.

		system("umount /Volumes/iOS");
		printf("Unmounted VDisk\n");
		sleep(1);
		printf("Preparing To Invert iOS APFS Disk\n");
	//	setup to run apfs invert
	//	printf("%s", invapfscom);
		printf("\n");
		system(invapfscom);
		printf("\nImage Success.. Compressing\n");
		sleep(3);
		printf("Mount iOS VDisk..\n");
		system("hdiutil attach iOS.dmg  >/dev/null 2>&1");
		printf("\nConnecting..\n");
		//Allow disk to mount
		sleep(7);
		printf("\nConnected.\n");
		sleep(2);
		system("tar -zcf  iOSout.tar.gz /Volumes/iOS  >/dev/null 2>&1");

		//iOS.dmg no longer neccessary. New code will unmount iOS dmg regardless of user response, wait for disconnect
		//And offer to remove/clean the file for convenience and an extra 16GB disk space :)

		printf("\niOS Succesfully Compressed.\nUnmounting iOS VDisk\n");
		//Check if sudo is necessary for unmounting disks.
		//system("sudo umount /Volumes/iOS");
		printf("\nDisk was succesfully unmounted..\n");


		printf("Clean iOS VDisk? (0/1)\n");
		int opt1;
		scanf("%d", &opt1);
		switch(opt1){
			case 0:
				printf("Skipping Process..\n");
				break;
			case 1:
				printf("Cleaning iOS VDisk..\n");
				//system("rm iOS.dmg");
				printf("iOS VDisk has been removed!\n");
				sleep(3);
				break;
			default:
				printf("Didn't understand your response.. Skipping Process..\n");
				break;
		}

		printf("\nProcess Complete\n");
		//End of new code.
}