//usr/bin/gcc "$0" && exec ./a.out "$@" && rm a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef defined(_WIN32) || defined(WIN32)

	#include <Windows.h>

#else

	#include <time.h>
	#include <errno.h>

	int msleep(long msec)
	{
		struct timespec ts;
		int res;

		if (msec < 0)
		{
			errno = EINVAL;
			return -1;
		}

		ts.tv_sec = msec / 1000;
		ts.tv_nsec = (msec % 1000) * 1000000;

		do {
			res = nanosleep(&ts, &ts);
		} while (res && errno == EINTR);

		return res;
	}

#endif

void music(char* musicFile)
{
	char cmd[strlen(musicFile)+9];
	sprintf(cmd, "mpg123 %s &", musicFile);
	system(cmd);
}

int readTxt(char* imageFolder, int* i, int fps, int* time, int limit)
{
	if(++(*i) >= limit)
		return 2;

	#ifdef defined(_WIN32) || defined(WIN32)
		system("cls");
		char cmd[12+strlen(imageFolder)+((int)limit/1000)];
		sprintf(cmd, "type %sBA%d.txt", imageFolder, *i);
	#else
		system("clear");
		char cmd[11+strlen(imageFolder)+((int)limit/1000)];
		sprintf(cmd, "cat %sBA%d.txt", imageFolder, *i);
	#endif

	return system(cmd);
}

int main(int argc, char** argv)
{
	int musicFileLength = 0;
	int imageFolderLength = 0;

	if(argc >= 2)
	{
		musicFileLength = strlen(argv[1]);
		if(argc >= 3)
		{
			imageFolderLength = strlen(argv[2]);
		}
	}
	else
	{
		musicFileLength = 13;
		imageFolderLength = 11;
	}

	char musicFile[musicFileLength];
	char imageFolder[imageFolderLength];

	if(argc >= 2)
	{
		strcpy(musicFile, argv[1]);
		if(argc >= 3)
		{
			strcpy(imageFolder, argv[2]);
		}
	}
	else
	{
		strcpy(musicFile, "../music.mp3");
		strcpy(imageFolder, "../images/");
	}

	music(musicFile);

	const int fps = 45;
	const int limit = 6570; // Number of frames + 1

	int i = 1;
	int time = 0;

	int r = 0;

	while(1)
	{
		#if defined(_WIN32) || defined(WIN32)
			Sleep((int) 1000/fps);
		#else
			msleep((int) 1000/fps);
		#endif

		r = readTxt(imageFolder, &i, fps, &time, limit);
		switch(r)
		{
			case 1:
				printf("[BADAPPLE] Error reading file %d.txt\n", i);
				return 1;
				break;

			case 2:
				puts("[BADAPPLE] END\n");
				return 0;
				break;
		};
		time += 1000;
	}

	return 0;
}
