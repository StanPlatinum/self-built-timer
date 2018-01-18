#include <sys/ipc.h>
#include <sys/shm.h>

#include "spec.h"

#define OAKLAND_SENDER 15

int shmid1, shmid2, shmid3, shmid4, shmid5, shmid6, shmid7, shmid8;

/* functions that create huge pages */
char * init_hugetlb_seg_1page(int pageno)
{
	int i;
	char * a = NULL;
	shmid1 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid1 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid1);
	a = shmat(shmid1, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid1, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'A';
	return a;
}

char * init_hugetlb_seg_ano_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid2 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid2 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid2);
	a = shmat(shmid2, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid2, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'B';
	return a;
}

char * init_hugetlb_seg_3rd_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid3 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid3 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid3);
	a = shmat(shmid3, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid3, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'C';
	return a;
}

char * init_hugetlb_seg_4th_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid4 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid4 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid4);
	a = shmat(shmid4, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid4, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'D';
	return a;
}

char * init_hugetlb_seg_5th_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid5 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid5 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid5);
	a = shmat(shmid5, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid5, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'E';
	return a;
}

char * init_hugetlb_seg_6th_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid6 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid6 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid6);
	a = shmat(shmid6, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid6, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'F';
	return a;
}

char * init_hugetlb_seg_7th_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid7 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid7 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid7);
	a = shmat(shmid7, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid7, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'F';
	return a;
}

char * init_hugetlb_seg_8th_page(int pageno)
{
	int i;
	char * a = NULL;
	shmid8 = shmget(OAKLAND_SENDER + pageno, L3_SLICE_NUM, SHM_HUGETLB
			| IPC_CREAT | SHM_R | SHM_W);
	if (shmid8 < 0) {
		perror("shmget error!");
		exit(1);
	}
	printf("HugeTLB shmid 0x%x. ", shmid8);
	a = shmat(shmid8, 0, 0);
	if (a == (char *)-1) {
		perror("shared memory attach failure!");
		shmctl(shmid8, IPC_RMID, NULL);
		exit(2);
	}

	printf("start writing...\n");
	for(i = 0; i < L3_SLICE_NUM; i++)
		a[i] = 'F';
	return a;
}
