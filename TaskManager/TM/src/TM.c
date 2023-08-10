/*
 ============================================================================
 Name        : TM.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TITLE_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200
#define FILENAME "tasks.txt"

struct Task {
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char due_date[20];
    int priority;
};

struct Task taskList[MAX_TASKS];
int numTasks = 0;

void saveTasksToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numTasks; ++i) {
        fprintf(file, "%s|%s|%s|%d\n",
                taskList[i].title, taskList[i].description,
                taskList[i].due_date, taskList[i].priority);
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

void loadTasksFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No saved tasks found.\n");
        return;
    }

    numTasks = 0;
    while (fgets(taskList[numTasks].title, sizeof(taskList[numTasks].title), file)) {
        fgets(taskList[numTasks].description, sizeof(taskList[numTasks].description), file);
        fgets(taskList[numTasks].due_date, sizeof(taskList[numTasks].due_date), file);
        fscanf(file, "%d\n", &taskList[numTasks].priority);
        ++numTasks;
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}

void createTask() {
    if (numTasks < MAX_TASKS) {
        struct Task newTask;
        printf("Enter task title: ");
        fgets(newTask.title, sizeof(newTask.title), stdin);
        printf("Enter task description: ");
        fgets(newTask.description, sizeof(newTask.description), stdin);
        printf("Enter due date: ");
        fgets(newTask.due_date, sizeof(newTask.due_date), stdin);
        printf("Enter priority (1-5): ");
        scanf("%d", &newTask.priority);
        getchar();  // Consume newline character
        taskList[numTasks++] = newTask;
        printf("Task added successfully!\n");
    } else {
        printf("Task list is full!\n");
    }
}

void listTasks() {
    if (numTasks == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("Task List:\n");
    for (int i = 0; i < numTasks; ++i) {
        printf("Task %d:\n", i + 1);
        printf("Title: %s", taskList[i].title);
        printf("Description: %s", taskList[i].description);
        printf("Due Date: %s", taskList[i].due_date);
        printf("Priority: %d\n", taskList[i].priority);
    }
}

void editTask() {
    int taskIndex;
    printf("Enter the index of the task to edit: ");
    scanf("%d", &taskIndex);
    getchar(); // Consume newline character

    if (taskIndex >= 1 && taskIndex <= numTasks) {
        struct Task *task = &taskList[taskIndex - 1];
        printf("Enter new task title: ");
        fgets(task->title, sizeof(task->title), stdin);
        printf("Enter new task description: ");
        fgets(task->description, sizeof(task->description), stdin);
        printf("Enter new due date: ");
        fgets(task->due_date, sizeof(task->due_date), stdin);
        printf("Enter new priority (1-5): ");
        scanf("%d", &task->priority);
        getchar(); // Consume newline character
        printf("Task updated successfully!\n");
    } else {
        printf("Invalid task index.\n");
    }
}

void deleteTask() {
    int taskIndex;
    printf("Enter the index of the task to delete: ");
    scanf("%d", &taskIndex);
    getchar(); // Consume newline character

    if (taskIndex >= 1 && taskIndex <= numTasks) {
        for (int i = taskIndex - 1; i < numTasks - 1; ++i) {
            taskList[i] = taskList[i + 1];
        }
        numTasks--;
        printf("Task deleted successfully!\n");
    } else {
        printf("Invalid task index.\n");
    }
}

int compareTasks(const void *task1, const void *task2) {
    return ((struct Task *)task1)->priority - ((struct Task *)task2)->priority;
}

void sortTasksByPriority() {
    qsort(taskList, numTasks, sizeof(struct Task), compareTasks);
    printf("Tasks sorted by priority.\n");
}

int main() {
    int choice;

    loadTasksFromFile();

    do {
        printf("\nTask Manager Menu:\n");
        printf("1. Create Task\n");
        printf("2. List Tasks\n");
        printf("3. Edit Task\n");
        printf("4. Delete Task\n");
        printf("5. Sort Tasks by Priority\n");
        printf("6. Save Tasks to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                createTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                editTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                sortTasksByPriority();
                break;
            case 6:
                saveTasksToFile();
                break;
            case 7:
                saveTasksToFile();
                printf("Exiting Task Manager.\n");
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (1);

    return 0;
}

