#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Q8 8 // time quantum for Q0 - RR
#define Q16 16 // time quantum for Q1 - RR

int current_time;

// struct to store process control block (struct PCP) information
struct PCP {
	int id;
	int arrivalTime; // arrival time of the process
	int burstTime; // total burst time for the process
	int remainingTime; // remaining burst time for the process
	int waitingTime; // waiting time for the process
	int responseTime; // response time for the process
	int completion_time; // completion time for the process
	int TAT;
	bool completed; // flag to indicate if the process is completed


};

void sortByArrival(struct PCP processes[], int num_processes) {
	struct PCP t;
	for (int i = 0; i < num_processes - 1; i++)
	{
		for (int j = i + 1; j < num_processes; j++) {
			if (processes[i].arrivalTime > processes[j].arrivalTime) {
				t = processes[i];
				processes[i] = processes[j];
				processes[j] = t;
			}
		}
	}
}

void sortByID(struct PCP processes[], int num_processes) {
	struct PCP t;
	for (int i = 0; i < num_processes - 1; i++)
	{
		for (int j = i + 1; j < num_processes; j++) {
			if (processes[i].id > processes[j].id) {
				t = processes[i];
				processes[i] = processes[j];
				processes[j] = t;
			}
		}
	}
}


// function to implement the Multilevel-feedback-queue scheduler
void RRQ8(struct PCP processes[], int num_processes) {
    
	sortByArrival(processes, num_processes);
	current_time = processes[0].arrivalTime;
	for (int i = 0; i < num_processes; i++) {
		if (processes[i].remainingTime > Q8) {
			processes[i].responseTime = current_time;
			current_time += Q8;
			processes[i].remainingTime -= Q8;
		}
		else {
			processes[i].responseTime = current_time;
			current_time += processes[i].remainingTime;
			processes[i].completed = true;
			processes[i].completion_time = current_time;
			processes[i].remainingTime = 0;
		}
	}
	sortByID(processes, num_processes);
}

void RRQ16(struct PCP processes[], int num_processes) {
    
	sortByArrival(processes, num_processes);
	for (int i = 0; i < num_processes; i++) {

		if (!processes[i].completed) {
			if (processes[i].remainingTime > Q16) {
				current_time += Q16;
				processes[i].remainingTime -= Q16;
			}
			else {
				current_time += processes[i].remainingTime;
				processes[i].completed = true;
				processes[i].completion_time = current_time;
				processes[i].remainingTime = 0;
			}
		}
	}
	sortByID(processes, num_processes);
}

// function to calculate the waiting time, response time and completion time for each process
void FCFS(struct PCP processes[], int num_processes) {
	sortByArrival(processes, num_processes);
	for (int i = 0; i < num_processes; i++) {
		if (!processes[i].completed) {
			current_time += processes[i].remainingTime;
			processes[i].completion_time = current_time;
			processes[i].completed = true;
			processes[i].remainingTime = 0;
		}
	}
	sortByID(processes, num_processes);
}



int main() {
	int n;
	int run = 1;
	struct PCP processes[20];
	double AWT = 0;

	while (run == 1) {
		printf("*********************************************************\n");
		printf("WELCOME:)\n\n  Enter number of processes you want to calculated(at most 20): ");
		scanf("%d", &n);
		while (n > 10) {
			printf("***Please enter less than 20: ");
			scanf("%d", &n);
		}
		printf("\n");
		for (int i = 0; i < n; i++)
		{
			printf("*Process number %d\n", i + 1);

			printf("******The arrival time: ");
			scanf("%d", &processes[i].arrivalTime);

			printf("******The brust Time: ");
			scanf("%d", &processes[i].burstTime);
			processes[i].remainingTime = processes[i].burstTime;
			printf("\n");
			processes[i].id = i + 1;

		}
		///////////////////////////
		RRQ8(processes, n);
		RRQ16(processes, n);
		FCFS(processes, n);
		///////////////////////////
		
		printf("****************************************************************************************");
		printf("\nProcess\t\t\tWaiting Time\t\tResponse Time\t\tTurn Around Time");

		for (int i = 0; i < n; i++)
		{
			processes[i].waitingTime = processes[i].completion_time - processes[i].arrivalTime - processes[i].burstTime;
			processes[i].TAT = processes[i].completion_time - processes[i].arrivalTime;
			AWT += processes[i].waitingTime;
			printf("\n%d\t\t\t%d\t\t\t%d\t\t\t%d", i+1, processes[i].waitingTime, processes[i].responseTime, processes[i].TAT);
		}
		AWT /= n;
		float Throughput =(float) n / current_time;
		printf("\n****************************************************************************************\n");
		printf("\n******The avarage waiting time: %.2f\n", AWT);
		printf("******The Throughput: %.2f\n", Throughput);

		printf("\nDo you want calculate to another processes :) ?\n1- Yes\n2- No\n");
		scanf("%d", &run);
		while (run > 2 || run < 0) {
			printf("please choose a number: ");
			scanf("%d", &run);
		}
		AWT = 0;
	}
}
