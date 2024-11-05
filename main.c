#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a1_functions.h"
#include "a1_data_structures.h"
#define MAX_MILESTONES 5
#define MAX_ACTIVITIES 3
#define MAX_NAME_LENGTH 50






int main()
{ 

    /** 1-  Display a welcome message **/
    printf("Welcome to ABC Company's Project Management Software!\n");

    /** 2- Get the project's name and number of milestones **/
    char project_name[MAX_NAME_LENGTH];
    int num_milestones;
    printf("Enter the project name (no spaces): ");
    scanf("%s", project_name);
    do{
        printf("\nEnter the number of milestones (1 to 5). ");
        num_milestones = get_input_usi();
        if (num_milestones < 1 || num_milestones > MAX_MILESTONES){
            printf("Invalid number of milestones. Please enter a value between 1 and 5.\n");
        }
    }while (num_milestones < 1 || num_milestones > MAX_MILESTONES);


    
  
    milestone_t milestone_list[MAX_MILESTONES]; 
    //Stores the number of activities each milestone has
    int number_activities[MAX_MILESTONES];    

    for (int i = 0; i < num_milestones; i++){
        do{
            printf("Enter the number of activities for milestone %d (1 to 3). ", i + 1);
            number_activities[i] = get_input_usi();
            if (number_activities[i] < 1 || number_activities[i] > MAX_ACTIVITIES){
                printf("Invalid number of activities. Please enter a value between 1 and 3.\n");
            }
        }while (number_activities[i] < 1 || number_activities[i] > MAX_ACTIVITIES);

        init_milestone(&milestone_list[i], number_activities[i]);
    }

    check_dupes_activity_ids(milestone_list, num_milestones, number_activities);
    check_dupes_milestone_ids(milestone_list, num_milestones);

    
    
    project_t my_project = init_project(project_name, milestone_list, num_milestones, number_activities);
    

   
    int user_choice;
    do{ 
        print_main_menu();
        user_choice = get_input_usi();

    
        switch (user_choice) {
            //Update activity
            case 1: 
                for (int i = 0; i < num_milestones; i++){
                    printf("Milestone %d - %s\n", milestone_list[i].id, milestone_list[i].name);
                    for (int j = 0; j < number_activities[i]; j++){
                        printf("Activity ID: %d (%s) (Completed: %s)\n", milestone_list[i].activity_list[j].id, 
                               milestone_list[i].activity_list[j].name, 
                               milestone_list[i].activity_list[j].completed ? "Yes" : "No");
                    }
                }
                _Bool found;
                do{
                    printf("Enter the ID of the activity to update. ");
                    int activity_id = get_input_usi();

                    found = false; 

                    for (int i = 0; i < num_milestones; i++){
                        for (int j = 0; j < number_activities[i]; j++){
                            if (milestone_list[i].activity_list[j].id == activity_id){
                                if (!milestone_list[i].activity_list[j].completed){
                                    update_activity(&milestone_list[i].activity_list[j]);
                                    update_project(milestone_list, num_milestones, number_activities, &my_project);
                                    found = true;
                                    break; 
                                }
                            }   
                        }
                        if (found) {
                            break;
                            }
                    }
                    if (!found){
                        printf("Invalid activity ID. Please try again.\n");
                    }
                }while (!found);
                break;    
           
            //Print stats
            case 2: 
                print_project_stats(my_project, milestone_list, num_milestones, number_activities);
                break;

            case 3: //Exit
                printf("Goodbye!, quitting the program.\n");
                break;

            default:
                printf("Invalid option. Please select between 1 and 3.\n");
        }
    }while (user_choice != 3);

    return 0;

   

    
    

    return EXIT_SUCCESS;
}
