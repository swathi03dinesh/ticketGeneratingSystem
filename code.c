#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int dest, board;
char c;
char loc[][30] = {
    "ALUVA", "PULINCHODU", "COMPANYPADI", "AMBATTUKAVU", "MUTTOM", "KALAMASSERY", "CUSAT", "PATHADIPALAM", "EDAPALLY", "CHANGAMPUZHA PARK",
    "PALARIVATTOM", "JLN STADIUM", "KALOOR", "TOWN HALL", "MG ROAD", "MAHARAJAS COLLEGE", "ERNAKULAM SOUTH", "KADAVANTHRA", "ELAMKULAM", "VYTTILA",
    "THYKOODAM", "PETTA"
};

struct details {
    char name[50];
    char boarding[50], destination[50];
    int premium;
} a[6];

void station_display() {
    int l = 22;
    printf("\n----------------------------------STATIONS----------------------------------\n");
    for (int i = 0; i < l; i++) {
        printf("%d. %s ", i + 1, loc[i]);
    }
    printf("\n-----------------------------------------------------------------------------\n");
}

int check_id(char name[50]) {
    FILE *p;
    int i, id;
    char name1[50];
    p = fopen("premiumusers.txt", "r");
    while (feof(p) == 0) {
        fscanf(p, "%s %d", name1, &id);

        if (strcmp(name1, name) == 0) {
            printf("ENTER YOUR ID: ");
            scanf("%d", &i);
            if (id == i)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

float get_rate(int stops, int premium) {
    float rate = stops * 5;
    if (premium)
        rate = rate - rate / 10;
    return rate;
}

void get_ticket(struct details b, float rate, int platform) {
    printf("\n-----------------------------------------------------------------------------\n");
    printf("WELCOME TO KOCHI METRO RAIL LTD.\n\n");
    if (b.premium) {
        printf("PREMIUM USER\n");
        printf("\n");
    }
    printf("NAME:\t%s\n", b.name);
    printf("BOARDING STATION: %s\n", b.boarding);
    printf("DESTINATION: %s\n", b.destination);
    printf("RATE FOR THE COMMUTE: %.2f\n", rate);
    printf("PLATFORM FOR YOUR COMMUTE IS %d\n", platform);
    printf("THANK YOU FOR USING KOCHI METRO!\n");
    printf("\n-----------------------------------------------------------------------------\n");
}

void boarding(int index) {
    station_display();
    printf("\nENTER THE BOARDING PLACE: ");

    scanf("%d", &board);
    while (board > 22 || board <= 0) {
        printf("\nINVALID BOARDING ADDRESS!\n");
        printf("\nENTER THE BOARDING PLACE: ");
        scanf("%d", &board);
    }
    printf("\nENTER DESTINATION PLACE: ");
    scanf("%d", &dest);
    while (dest > 22 || dest <= 0) {
        printf("\nINVALID DESTINATION ADDRESS!\n");
        printf("\nENTER DESTINATION PLACE: ");
        scanf("%d", &dest);
    }
    if (board == dest) {
        printf("\nINVALID DESTINATION\n");
        printf("\nENTER DESTINATION PLACE: ");
        scanf("%d", &dest);
    }
    strcpy(a[index].destination, loc[dest - 1]);
    strcpy(a[index].boarding, loc[board - 1]);
    int platform, stops;
    if (board < dest) {
        platform = 1;
        stops = dest - board;
    } else {
        platform = 2;
        stops = board - dest;
    }
    int premium;
    printf("\nARE YOU A PREMIUM USER? y/n: ");
    scanf(" %c", &c);
    if (tolower(c) == 'y') {
        printf("\nENTER YOUR NAME: ");
        scanf("%s", a[index].name);
        printf("\nNAME is:%s \nBOARDING STN:%s\nDESTINATION:%s\n", a[index].name, a[index].boarding, a[index].destination);

        premium = check_id(a[index].name);
        if (premium == 0)
            printf("\nINVALID ID/NAME\n");
    } else {
        printf("\nENTER YOUR NAME: ");
        scanf("%s", a[index].name);
        premium = 0;
    }
    a[index].premium = premium;
    float rate;
    rate = get_rate(stops, premium);
    printf("\nRATE FROM %s TO %s IS %.2f for: %s\n", a[index].boarding, a[index].destination, rate, a[index].name);
    getchar();
}

int main() {
    system("clear");
    int n;
    printf("\nENTER THE NUMBER OF COMMUTERS: ");
    scanf("%d", &n);
    if (n > 6)
        printf("OOPS! ONLY 6 TICKETS CAN BE BOOKED AT ONCE\n");
    else {
        for (int i = 0; i < n; i++)
            boarding(i);
    }
    return 0;
}
