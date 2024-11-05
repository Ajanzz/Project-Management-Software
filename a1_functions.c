#include "a1_functions.h"
#include "a1_data_structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAX_MILESTONES 5
#define MAX_ACTIVITIES 3
#define HOURLY_SALARY 30
#define HOURS_DAY 8
#define MAX_NAME_LENGTH 50

unsigned short int get_input_usi(void){
	int value;
	printf("Enter a positive integer input: ");
	do{
		scanf("%d", &value);
		if (value < 0){
			printf("Invalid input. Please enter a positive value.\n");
		}
	}while(value < 0);

	return (unsigned short)value;
}


float get_input_f(void){
	float value;
	printf("Enter a positive float input: ");
	do{
		scanf("%f", &value);
		if (value < 0){
			printf("Invalid input. Please enter a positive value.\n");
		}
	}while(value < 0);

	return value;
}


void init_activity(activity_t *activity_to_int){
    printf("Initializing activity, what is activity ID. ");
	activity_to_int->id = get_input_usi();;
	printf("Enter the name for the activity: ");
	char act_name[MAX_NAME_LENGTH];
	scanf("%s", &act_name);
	strcpy(activity_to_int->name, act_name);
	activity_to_int -> actual_cost = 0;
	printf("Enter planned duration of hours. ");
	activity_to_int -> planned_duration = get_input_usi();
	activity_to_int -> planned_cost = (activity_to_int -> planned_duration) * HOURLY_SALARY;
	activity_to_int -> actual_duration = 0;
	activity_to_int -> completed = 0;
}

void init_milestone(milestone_t *milestone_to_int, unsigned short int num_activities){
   
    printf("Initializing milestone, what is milestone ID. \n");
	//Initializing the milestone fields
	milestone_to_int->id = get_input_usi();
	printf("Enter milestone name: ");
	char mile_name[MAX_NAME_LENGTH];
	scanf("%s", &mile_name);
	strcpy(milestone_to_int->name, mile_name);
	milestone_to_int->actual_cost = 0;
	milestone_to_int->actual_duration = 0;
	milestone_to_int->completed = 0;

	for (int i = 0; i < num_activities; i++){
		printf("\nInitializing activity %hu in %s: \n", i + 1, milestone_to_int -> name);
		init_activity(&milestone_to_int->activity_list[i]);
	}

}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int *number_activities){
	project_t project;
	
	//Initializing the project fields
	strcpy(project.name, name);
	project.planned_cost = 0;
	project.actual_cost = 0;
	project.planned_duration = 0;
	project.actual_duration = 0;
	project.completed = 0;

	//Calculating the planned cost and duration for the projct
	for (int i = 0; i < number_milestones; i++){
		for (int j = 0; j < number_activities[i]; j++){
        	project.planned_cost += milestone_list[i].activity_list[j].planned_cost;
        	project.planned_duration += milestone_list[i].activity_list[j].planned_duration;
        }
	}
	return project;


}


void print_main_menu(void){
	printf("_________________________________________________________________");
	printf("\nMain Menu:\n");
    printf("1. Update Activity\n");
    printf("2. View Project Stats\n");
    printf("3. Exit\n");
    printf("Enter your choice. ");
}



void print_milestone_stats(const milestone_t *list_milestones, int num_milestones, const int *number_activities){
    
	float milestone_planned_cost[num_milestones];
	unsigned short int milestone_planned_duration[num_milestones];
	for (int i = 0; i < num_milestones; i++){
        const milestone_t *milestone = &list_milestones[i];
		milestone_planned_cost[i] = 0;
		milestone_planned_duration[i] = 0;
		for (int k = 0; k < number_activities[i]; k++){
            const activity_t *activity = &milestone->activity_list[k];
            milestone_planned_cost[i] += activity->planned_cost;
			milestone_planned_duration[i] += activity->planned_duration;
        }

		//How the milestone stats are printed if milestone is completed vs not completed
		if (milestone->completed){
			printf("\nMilestone ID: %d, Milestone Name: %s:\n", milestone->id, milestone->name);
			printf("It was $%.2f %s budget\n",fabs(milestone -> actual_cost - milestone_planned_cost[i]),milestone -> actual_cost > milestone_planned_cost[i] ? "over" : "under");
			printf("It was %.0f days %s the planned duration\n",ceil(fabs(milestone -> actual_duration - milestone_planned_duration[i])/HOURS_DAY),milestone -> actual_duration > milestone_planned_duration[i] ? "over" : "under");

		}else{
        	printf("\nMilestone ID: %d, Milestone Name: %s:\n", milestone->id, milestone->name);
        	printf("Planned cost: $%.2f\n", milestone_planned_cost[i]);
        	printf("Planned duration: %d hours\n", milestone_planned_duration[i]);
        	int activity_completion_count = 0;
			//Counting how many of the acivities are completed per each milestone
			for (int j = 0; j < number_activities[i]; j++){
            	const activity_t *activity = &milestone->activity_list[j];
				if (activity -> completed){
					activity_completion_count+=1;
					}
        		}
			printf("%d out of %d activities completed in milestone\n",activity_completion_count, number_activities[i]);
			printf("Completed: %s\n", milestone->completed ? "Yes" : "No");
		}
    }
}



void print_project_stats(project_t details, const milestone_t *list_milestones, int num_milestones, const int *number_activities){
    printf("\nProject: %s\n", details.name);
	printf("Completed: %s\n", details.completed ? "Yes" : "No");

	//How the project stats print if project is completed vs not completed
	if (details.completed){
		printf("It was $%.2f %s budget.\n",fabs(details.actual_cost - details.planned_cost),details.actual_cost > details.planned_cost ? "over" : "under");
		printf("It was completed %.0f day/s %s than planned.\n",ceil(fabs(details.actual_duration - details.planned_duration)/HOURS_DAY),details.actual_duration > details.planned_duration ? "later" : "earlier");
	}else{
    	print_milestone_stats(list_milestones, num_milestones, number_activities);
	}
    
}



void update_activity(activity_t *activity_to_update){
	char completion;
    printf("Updating %s:\n", activity_to_update->name);
    printf("Enter actual duration (hours). ");
    activity_to_update->actual_duration = get_input_usi();
    activity_to_update->actual_cost = (activity_to_update->actual_duration) * HOURLY_SALARY;
    printf("Is the activity completed? (Y for Yes, N or any other character for No). ");
	scanf(" %c", &completion);
    activity_to_update->completed = (completion == 'Y' || completion == 'y') ? 1 : 0;
}


void update_milestone(milestone_t *milestone_to_update, int activities_in_milestone) {
    printf("Updating milestone %s:\n", milestone_to_update->name);
    milestone_to_update->completed = 1;
	milestone_to_update->actual_cost = 0;
	milestone_to_update->actual_duration = 0;
    for (int i = 0; i < activities_in_milestone; i++){
		milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
		milestone_to_update->actual_duration += milestone_to_update -> activity_list[i].actual_duration;
        if (!milestone_to_update->activity_list[i].completed) {
            milestone_to_update->completed = 0;
            break;
        }
    }
}

void update_project(const milestone_t *milestone_array, int num_milestones, const int *number_activities, project_t *my_project){
    
    my_project->actual_cost = 0;
    my_project->actual_duration = 0;
    my_project->completed = 1;  

    for (int i = 0; i < num_milestones; i++){
        update_milestone((milestone_t *)&milestone_array[i], number_activities[i]);
        my_project->actual_cost += milestone_array[i].actual_cost;
        my_project->actual_duration += milestone_array[i].actual_duration;
        if (!milestone_array[i].completed) {
            my_project->completed = 0;
        }
    }
}




void check_dupes_activity_ids(milestone_t milestone_list[], int num_milestones, int number_activities[]){
    unsigned short activity_ids[MAX_MILESTONES * MAX_ACTIVITIES];
    int activity_count = 0;
    for (int i = 0; i < num_milestones; i++){
        for (int j = 0; j < number_activities[i]; j++){
            for (int k = 0; k < activity_count; k++){
                if (milestone_list[i].activity_list[j].id == activity_ids[k]){
                    printf("Duplicate activity ID found \n");
                    unsigned short new_id;
                    _Bool is_duplicate;
                    do{
                        is_duplicate = false;
                        printf("Please enter a new unique activity ID for activity %s ", milestone_list[i].activity_list[j].name );
                        new_id = get_input_usi();
                        for (int l = 0; l < activity_count; l++) {
                            if (new_id == activity_ids[l]) {
                                printf("%d is already in use. Please enter a unique activity ID.\n", new_id);
                                is_duplicate = true;  
                                break; 
                            }
                        }
                    }while (is_duplicate); 
                    milestone_list[i].activity_list[j].id = new_id;
                    printf("Updated activity ID to: %d\n", milestone_list[i].activity_list[j].id);
                    break; 
                }
            }     
            activity_ids[activity_count++] = milestone_list[i].activity_list[j].id;
        }
    }
}


void check_dupes_milestone_ids(milestone_t milestone_list[], int num_milestones) {
    unsigned short milestone_ids[MAX_MILESTONES];
    int milestone_count = 0;
    for (int i = 0; i < num_milestones; i++){ 
        for (int j = 0; j < milestone_count; j++){
            if (milestone_list[i].id == milestone_ids[j]) {
                printf("Duplicate milestone ID found.");
                unsigned short new_id;
                _Bool duplicate;
                do{
                	duplicate = false; 
                    printf("Please enter a new unique milestone ID for milestone %s.", milestone_list[i].name);
                    new_id = get_input_usi();
                    for (int l = 0; l < milestone_count; l++) {
                        if (new_id == milestone_ids[l]) {
                            printf("%d is already used. Please enter a new milestone ID.\n", new_id);
                            duplicate = true; 
                            break;  
                        }
                    }
                }while (duplicate);
                milestone_list[i].id = new_id;
                printf("Updated milestone ID to  %d\n", milestone_list[i].id);
                break; 
            }
        }
        milestone_ids[milestone_count++] = milestone_list[i].id;
    }
}
