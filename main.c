
#include <stdio.h>
#include <string.h>

#define DAYS 6
#define PERIODS 5

char timetable[DAYS][PERIODS][50] = {
    {"C Programming", "Mathematics", "English", "Physics", "Lab"},
    {"Mathematics", "C Programming", "Physics", "English", "Lab"},
    {"English", "Physics", "Mathematics", "C Programming", "Lab"},
    {"Physics", "English", "C Programming", "Mathematics", "Lab"},
    {"C Programming", "Mathematics", "Physics", "English", "Lab"},
    {"English", "C Programming", "Mathematics", "Physics", "Lab"}
};

char *days[DAYS] = {
    "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};
#define ITEMS 5

char canteenItems[ITEMS][50] = {
    "Samosa",
    "Sandwich",
    "Burger",
    "Cold Drink",
    "Maggi"
};

float canteenPrices[ITEMS] = {
    15, 40, 50, 30, 40
};
#define MAX_EVENTS 50

char eventNames[MAX_EVENTS][100];
char eventDates[MAX_EVENTS][30];

int eventCount = 0;
struct Student {
    int roll;
    char name[50];
    int totalDays;
    int presentDays;
};

void attendance() {
    int choice, roll, status;
    struct Student s[100];
    int count = 0, found = 0;
    FILE *fp;

    fp = fopen("attendance.dat", "rb");

    if (fp != NULL) {
        while (count < 100 &&
               fread(&s[count], sizeof(struct Student), 1, fp) == 1) {
            count++;
        }
        fclose(fp);
    }

    do {
        printf("\n--- STUDENT ATTENDANCE ---\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. View Attendance\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (count >= 100) {
                printf("Student limit reached!\n");
                continue;
            }

            printf("Enter roll number: ");
            scanf("%d", &s[count].roll);

            printf("Enter student name: ");
            scanf(" %49[^\n]", s[count].name);

            s[count].totalDays = 0;
            s[count].presentDays = 0;
            count++;

            fp = fopen("attendance.dat", "wb");
            if (fp != NULL) {
                fwrite(s, sizeof(struct Student), count, fp);
                fclose(fp);
                printf("Student added successfully!\n");
            }
        }

        else if (choice == 2) {
            printf("Enter roll number: ");
            scanf("%d", &roll);

            found = 0;

            for (int i = 0; i < count; i++) {
                if (s[i].roll == roll) {
                    printf("Enter 1 for Present, 0 for Absent: ");
                    scanf("%d", &status);

                    if (status == 0 || status == 1) {
                        s[i].totalDays++;
                        if (status == 1)
                            s[i].presentDays++;

                        found = 1;
                    } else {
                        printf("Invalid status!\n");
                        found = 1;
                    }
                    break;
                }
            }

            if (!found)
                printf("Student not found!\n");

            fp = fopen("attendance.dat", "wb");
            if (fp != NULL) {
                fwrite(s, sizeof(struct Student), count, fp);
                fclose(fp);
            }
        }

        else if (choice == 3) {
            for (int i = 0; i < count; i++) {
                float percentage = 0;

                if (s[i].totalDays > 0) {
                    percentage = (float)s[i].presentDays
                                 / s[i].totalDays * 100;
                }

                printf("\nRoll: %d", s[i].roll);
                printf("\nName: %s", s[i].name);
                printf("\nAttendance: %.2f%%\n", percentage);
            }
        }

    } while (choice != 4);
}
void saveTimetable()
{
    FILE *fp = fopen("timetable.txt", "w");

    if (fp == NULL)
    {
        printf("Error saving timetable!\n");
        return;
    }

    for (int i = 0; i < DAYS; i++)
    {
        for (int j = 0; j < PERIODS; j++)
        {
            fprintf(fp, "%s\n", timetable[i][j]);
        }
    }

    fclose(fp);
}

void loadTimetable()
{
    FILE *fp = fopen("timetable.txt", "r");

    if (fp == NULL)
        return;

    for (int i = 0; i < DAYS; i++)
    {
        for (int j = 0; j < PERIODS; j++)
        {
            if (fgets(timetable[i][j], 50, fp) != NULL)
            {
                timetable[i][j][strcspn(timetable[i][j], "\n")] = '\0';
            }
        }
    }

    fclose(fp);
}
void timetableMenu()
{
    int choice, day, period;
    loadTimetable();    

    while (1)
    {
        printf("\n===== TIMETABLE MENU =====\n");
        printf("1. View Timetable\n");
        printf("2. Update Timetable\n");
        printf("3. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            for (int i = 0; i < DAYS; i++)
            {
                printf("\n%s:\n", days[i]);

                for (int j = 0; j < PERIODS; j++)
                {
                    printf("Period %d: %s\n", j + 1, timetable[i][j]);
                }
            }
        }
        else if (choice == 2)
        {
            printf("Choose day (1-Monday to 6-Saturday): ");
            scanf("%d", &day);

            printf("Choose period (1-5): ");
            scanf("%d", &period);

            if (day >= 1 && day <= DAYS &&
                period >= 1 && period <= PERIODS)
            {
                printf("Enter new subject: ");
                scanf(" %49[^\n]", timetable[day - 1][period - 1]);
                saveTimetable();
                printf("Timetable updated successfully!\n");
            }
            else
            {
                printf("Invalid day or period!\n");
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}
void saveCanteen()
{
    FILE *fp = fopen("canteen.txt", "w");

    if (fp == NULL)
    {
        printf("Error saving canteen menu!\n");
        return;
    }

    for (int i = 0; i < ITEMS; i++)
    {
        fprintf(fp, "%s|%.2f\n",
                canteenItems[i], canteenPrices[i]);
    }

    fclose(fp);
}

void loadCanteen()
{
    FILE *fp = fopen("canteen.txt", "r");

    if (fp == NULL)
        return;

    for (int i = 0; i < ITEMS; i++)
    {
        if (fscanf(fp, "%49[^|]|%f\n",
                   canteenItems[i],
                   &canteenPrices[i]) != 2)
            break;
    }

    fclose(fp);
}
void canteenMenu()
{
    int choice, item;
    float price;
   loadCanteen(); 

    while (1)
    {
        printf("\n===== CANTEEN MENU =====\n");
        printf("1. View Canteen Menu\n");
        printf("2. Update Item and Price\n");
        printf("3. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\n===== AVAILABLE ITEMS =====\n");

            for (int i = 0; i < ITEMS; i++)
            {
                printf("%d. %s - Rs. %.2f\n",
                       i + 1, canteenItems[i], canteenPrices[i]);
            }
        }
        else if (choice == 2)
        {
            printf("Enter item number (1-5): ");
            scanf("%d", &item);

            if (item >= 1 && item <= ITEMS)
            {
                printf("Enter new item name: ");
                scanf(" %49[^\n]", canteenItems[item - 1]);

                printf("Enter new price: ");
                scanf("%f", &price);

                if (price >= 0)
                {
                    canteenPrices[item - 1] = price;
                saveCanteen();    
                    printf("Canteen item updated successfully!\n");
                }
                else
                {
                    printf("Invalid price!\n");
                }
            }
            else
            {
                printf("Invalid item number!\n");
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}
void saveEvents()
{
    FILE *fp = fopen("events.txt", "w");

    if (fp == NULL)
    {
        printf("Error saving events!\n");
        return;
    }

    for (int i = 0; i < eventCount; i++)
    {
        fprintf(fp, "%s|%s\n", eventNames[i], eventDates[i]);
    }

    fclose(fp);
}

void loadEvents()
{
    FILE *fp = fopen("events.txt", "r");

    if (fp == NULL)
        return;

    eventCount = 0;

    while (eventCount < MAX_EVENTS &&
           fscanf(fp, " %99[^|]|%29[^\n]",
                  eventNames[eventCount],
                  eventDates[eventCount]) == 2)
    {
        eventCount++;
    }

    fclose(fp);
}

void eventsMenu()
{
    int choice;

    loadEvents();

    while (1)
    {
        printf("\n===== COLLEGE EVENTS =====\n");
        printf("1. Add New Event\n");
        printf("2. View All Events\n");
        printf("3. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (eventCount >= MAX_EVENTS)
            {
                printf("Event list is full!\n");
                continue;
            }

            printf("Enter event name: ");
            scanf(" %99[^\n]", eventNames[eventCount]);

            printf("Enter event date: ");
            scanf(" %29[^\n]", eventDates[eventCount]);

            eventCount++;
            saveEvents();

            printf("Event added successfully!\n");
        }
        else if (choice == 2)
        {
            if (eventCount == 0)
            {
                printf("No events available!\n");
            }
            else
            {
                for (int i = 0; i < eventCount; i++)
                {
                    printf("\nEvent %d\n", i + 1);
                    printf("Name: %s\n", eventNames[i]);
                    printf("Date: %s\n", eventDates[i]);
                }
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}
int main() {
    int choice;

    do {
        printf("\n==============================\n");
        printf("   COLLEGE MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Student Attendance\n");
        printf("2. Timetable\n");
        printf("3. Canteen Menu\n");
        printf("4. College Events\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                attendance();
                break;

            case 2:
                timetableMenu();
                break;  

            case 3:
                canteenMenu();
                break;

            case 4:
                eventsMenu();   
                break;

            case 5:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
