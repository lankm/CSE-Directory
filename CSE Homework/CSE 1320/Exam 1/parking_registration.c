#include "parking_registration.h"

void trim(char *str) {
    int l = strlen(str);
    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

FILE *open_database(char *filename) {
    FILE *db = fopen(filename, "a+");
    return db;
}

/*
 * Parses a single line of CSV data representing vehicle_t information.
 */
vehicle_t parse_vehicle_csv(char *csv_line) {
    vehicle_t v = { 0 };
    char *token = strtok(csv_line, ",");
    int tokens_read = 0;

    while (token) {
        switch (tokens_read) {
            case 0:
                v.year = atoi(token);
                break;
            case 1:
                strcpy(v.make, token);
                break;
            case 2:
                strcpy(v.model, token);
                break;
            case 3:
                strcpy(v.color, token);
                break;
            case 4:
                strcpy(v.license, token);
                break;
        }

        tokens_read++;
        token = strtok(NULL, ",");
    }

    return v;
}

/*
 * Parses each line of CSV into a vehicle_t struct and prints it out.
 */
void view_database(FILE *db) {
    char buffer[BUF_SIZE] = { 0 };

    // Go back to the beginning of the file.
    rewind(db);

    while (fgets(buffer, BUF_SIZE, db)) {
        trim(buffer);

        vehicle_t v = parse_vehicle_csv(buffer);

        print_vehicle(v);
    }
}

void print_vehicle(vehicle_t v) {
    printf("%d %s %s (%s) LIC %s\n", v.year, v.make, v.model, v.color, v.license);
}

/*
 * Given a FILE pointer, this function should prompt the user to enter
 * vehicle information which is stored in a vehicle_t variable.
 * Prompt the user to confirm their entry, it should then be written as
 * CSV using write_data if the confirm and return 1, otherwise do not
 * write data and return 0.
 */
int register_vehicle(FILE *db) {
    vehicle_t v;

    int size=0;
    char buff[BUF_SIZE]={0};

    printf("Enter the vehicle year: ");
    fgets(buff, BUF_SIZE, stdin);
    v.year=atoi(buff);

    printf("Enter the vehicle make: ");
    fgets(buff, BUF_SIZE, stdin);
    trim(buff);
    strcpy(v.make, buff);

    printf("Enter the vehicle model: ");
    fgets(buff, BUF_SIZE, stdin);
    trim(buff);
    strcpy(v.model, buff);

    printf("Enter the vehicle color: ");
    fgets(buff, BUF_SIZE, stdin);
    trim(buff);
    strcpy(v.color, buff);

    printf("Enter the vehicle license: ");
    fgets(buff, BUF_SIZE, stdin);
    trim(buff);
    strcpy(v.license, buff);

    print_vehicle(v);
    printf("Is this information correct(y/n): ");
    fgets(buff, BUF_SIZE, stdin);
    trim(buff);

    if(!strcmp(buff,"y")) {
        printf("DEBUG\n");
        write_data(v, db);
        return 1;
    }
    else if(!strcmp(buff,"n")) {
        printf("Exiting to menu.");
        return 0;
    }
    else {
        printf("Invalid input. Exiting to menu.\n");
        return 0;
    }

    return 0;
}

/*
 * Writes the vehicle_t data to the file as CSV.
 */
void write_data(vehicle_t v, FILE *db) {
    fprintf(db, "%d,",v.year);
    fprintf(db, "%s,",v.make);
    fprintf(db, "%s,",v.model);
    fprintf(db, "%s,",v.color);
    fprintf(db, "%s\n",v.license);
}

int main(int argc, char **argv) {
    char choice = 0;
    char filename[MAX_STR] = "vehicles.csv";

    if (argc == 2) {
        strcpy(filename, argv[1]);
    }

    FILE *db = open_database(filename);

    if (!db) {
        printf("Unable to open database file.\n");
        return 1;
    }

    while (choice != 'q') {
        printf("R - Register Vehicle\n");
        printf("V - View Registered Vehicles\n");
        printf("Q - Quit\n");
        printf("Enter choice: ");
        choice=getchar();
        while (getchar() != '\n');
        choice = tolower(choice);

        switch (choice) {
            case 'r':
                if (register_vehicle(db)) {
                    printf("Vehicle registered!\n");
                }
                break;
            case 'v':
                view_database(db);
                break;
            case 'q':
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    }

    fclose(db);

    return 0;
}
