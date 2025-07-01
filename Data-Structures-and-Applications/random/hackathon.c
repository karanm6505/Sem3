#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -----------------------------
// Structure Definitions
// -----------------------------

// Structure for a person in each zone
typedef struct Person {
    char name[50];
    int isRescued;       // 1 if rescued, 0 otherwise
    int hasSupplies;     // 1 if the person has supplies, 0 otherwise
    struct Person *next;
} Person;

// Structure for each zone in the forest
typedef struct Zone {
    int id;
    int priority;        // 1 is highest priority, higher numbers are lower priority
    int supplies;        // Number of people who do not require rescuing
    int totalPeople;     // Total number of people in the zone
    int rescueCount;     // Number of people rescued from the zone
    Person *people;      // Linked list of people in the zone
    struct Zone *next;
} Zone;

// Node structure for the priority queue (sorted by priority)
typedef struct PriorityQueueNode {
    Zone *zone;
    struct PriorityQueueNode *next;
} PriorityQueueNode;

// Priority Queue structure
typedef struct PriorityQueue {
    PriorityQueueNode *head;
} PriorityQueue;

// Structure for the rescue team
typedef struct Team {
    int id;
    int rescuedCount;
    int supplies;        // Number of supplies the team has
    PriorityQueue *pq;   // Priority Queue for the team
} Team;

// Structure for rescued records (Binary Search Tree)
typedef struct RescuedRecord {
    char name[50];
    int zoneId;
    time_t rescueTime;
    struct RescuedRecord *left;
    struct RescuedRecord *right;
} RescuedRecord;

// -----------------------------
// Function Prototypes
// -----------------------------

// Priority Queue Operations
PriorityQueue* createPriorityQueue();
void enqueueZone(PriorityQueue *pq, Zone *zone);
Zone* dequeueZone(PriorityQueue *pq);
void displayZones(PriorityQueue *pq);

// Rescue Team Operations
void initializeTeam(Team *team, int id, int initialSupplies);
void displayTeam(Team *team);

// Binary Search Tree Operations for Rescued Records
RescuedRecord* createRescuedRecord(char* name, int zoneId);
RescuedRecord* insertRescuedRecord(RescuedRecord* root, char* name, int zoneId);
void inorderTraversal(RescuedRecord* root);
void displayRescuedPeople(RescuedRecord *root);

// Utility Functions
Person* createPerson(char* name, int hasSupplies);
Zone* createZone(int id, int priority, int supplies, int totalPeople);
void addPersonToZone(Zone *zone, Person *person);
void provideSupplies(Team *team, Zone *zone, int suppliesToProvide);
void displayUnrescuedPeople(Zone* zones[], int numZones);

// Memory Cleanup Functions
void freeRescuedRecords(RescuedRecord* root);
void freeZones(Zone* zones[], int numZones);

// -----------------------------
// Function Implementations
// -----------------------------

// Create an empty priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if(!pq) {
        fprintf(stderr, "Memory allocation failed for PriorityQueue.\n");
        exit(EXIT_FAILURE);
    }
    pq->head = NULL;
    return pq;
}

// Enqueue a zone into the priority queue based on its priority
void enqueueZone(PriorityQueue *pq, Zone *zone) {
    if(!pq || !zone) return;

    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    if(!newNode) {
        fprintf(stderr, "Memory allocation failed for PriorityQueueNode.\n");
        exit(EXIT_FAILURE);
    }
    newNode->zone = zone;
    newNode->next = NULL;

    // Insert in sorted order (ascending priority)
    if(pq->head == NULL || zone->priority < pq->head->zone->priority) {
        newNode->next = pq->head;
        pq->head = newNode;
    }
    else {
        PriorityQueueNode* current = pq->head;
        while(current->next != NULL && current->next->zone->priority <= zone->priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Dequeue a zone from the priority queue
Zone* dequeueZone(PriorityQueue *pq) {
    if(pq->head == NULL) {
        return NULL;
    }

    PriorityQueueNode* temp = pq->head;
    Zone* zone = temp->zone;
    pq->head = pq->head->next;
    free(temp);
    return zone;
}

// Display all zones in the priority queue
void displayZones(PriorityQueue *pq) {
    if(!pq) return;

    PriorityQueueNode* current = pq->head;
    printf("=== Current Zones in Priority Queue ===\n");
    while(current != NULL) {
        printf("Zone ID: %d, Priority: %d, Supplies: %d, Total People: %d, Rescued: %d\n", 
               current->zone->id, current->zone->priority, current->zone->supplies, 
               current->zone->totalPeople, current->zone->rescueCount);
        current = current->next;
    }
    printf("---------------------------------------\n");
}

// Initialize the rescue team
void initializeTeam(Team *team, int id, int initialSupplies) {
    if(!team) return;
    team->id = id;
    team->rescuedCount = 0;
    team->supplies = initialSupplies;
    team->pq = createPriorityQueue();
}

// Display the rescue team status
void displayTeam(Team *team) {
    if(!team) return;
    printf("Team %d - Rescued: %d, Supplies: %d\n", team->id, team->rescuedCount, team->supplies);
}

// Create a rescued record node
RescuedRecord* createRescuedRecord(char* name, int zoneId) {
    RescuedRecord* record = (RescuedRecord*)malloc(sizeof(RescuedRecord));
    if(!record) {
        fprintf(stderr, "Memory allocation failed for RescuedRecord.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(record->name, name, sizeof(record->name)-1);
    record->name[sizeof(record->name)-1] = '\0';
    record->zoneId = zoneId;
    record->rescueTime = time(NULL);
    record->left = record->right = NULL;
    return record;
}

// Insert a rescued record into the BST
RescuedRecord* insertRescuedRecord(RescuedRecord* root, char* name, int zoneId) {
    if(root == NULL) {
        return createRescuedRecord(name, zoneId);
    }

    if(difftime(time(NULL), root->rescueTime) > 0) {
        root->right = insertRescuedRecord(root->right, name, zoneId);
    }
    else {
        root->left = insertRescuedRecord(root->left, name, zoneId);
    }

    return root;
}

// In-order traversal of the BST
void inorderTraversal(RescuedRecord* root) {
    if(root == NULL) return;
    inorderTraversal(root->left);
    printf("Name: %s, Zone ID: %d, Rescued At: %s", root->name, root->zoneId, ctime(&root->rescueTime));
    inorderTraversal(root->right);
}

// Display all rescued people
void displayRescuedPeople(RescuedRecord *root) {
    printf("\n=== Final Rescued People ===\n");
    inorderTraversal(root);
    printf("---------------------------------------\n");
}

// Create a person
Person* createPerson(char* name, int hasSupplies) {
    Person* person = (Person*)malloc(sizeof(Person));
    if(!person) {
        fprintf(stderr, "Memory allocation failed for Person.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(person->name, name, sizeof(person->name)-1);
    person->name[sizeof(person->name)-1] = '\0';
    person->isRescued = 0;
    person->hasSupplies = hasSupplies;
    person->next = NULL;
    return person;
}

// Create a zone
Zone* createZone(int id, int priority, int supplies, int totalPeople) {
    Zone* zone = (Zone*)malloc(sizeof(Zone));
    if(!zone) {
        fprintf(stderr, "Memory allocation failed for Zone.\n");
        exit(EXIT_FAILURE);
    }
    zone->id = id;
    zone->priority = priority;
    zone->supplies = supplies;
    zone->totalPeople = totalPeople;
    zone->rescueCount = 0;
    zone->people = NULL;
    zone->next = NULL;
    return zone;
}

// Add a person to a zone's linked list
void addPersonToZone(Zone *zone, Person *person) {
    if(!zone || !person) return;

    if(zone->people == NULL) {
        zone->people = person;
    }
    else {
        Person *current = zone->people;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = person;
    }
}

// Provide additional supplies to a zone from the rescue team
void provideSupplies(Team *team, Zone *zone, int suppliesToProvide) {
    if(!team || !zone) return;

    if(team->supplies < suppliesToProvide) {
        suppliesToProvide = team->supplies;
    }

    zone->supplies += suppliesToProvide;
    team->supplies -= suppliesToProvide;
    printf("Provided %d supplies to Zone %d from Team %d.\n", suppliesToProvide, zone->id, team->id);
}

// Display all unrescued people across all zones
void displayUnrescuedPeople(Zone* zones[], int numZones) {
    int found = 0;
    printf("\n=== Unrescued People ===\n");
    for(int i = 0; i < numZones; i++) {
        Person* person = zones[i]->people;
        while(person != NULL) {
            if(!person->isRescued) {
                if(!found) {
                    printf("Unrescued People:\n");
                    found = 1;
                }
                printf("Name: %s, Zone ID: %d\n", person->name, zones[i]->id);
            }
            person = person->next;
        }
    }
    if(!found) {
        printf("All people have been rescued!\n");
    }
    printf("---------------------------------------\n");
}

// Free all rescued records in the BST
void freeRescuedRecords(RescuedRecord* root) {
    if (root == NULL) return;
    freeRescuedRecords(root->left);
    freeRescuedRecords(root->right);
    free(root);
}

// Free all zones and their associated people
void freeZones(Zone* zones[], int numZones) {
    for(int i = 0; i < numZones; i++) {
        Person* person = zones[i]->people;
        while(person != NULL) {
            Person* temp = person;
            person = person->next;
            free(temp);
        }
        free(zones[i]);
    }
}

// -----------------------------
// Main Function
// -----------------------------

int main() {
    // Create Rescue Teams
    Team team1, team2;
    initializeTeam(&team1, 1, 10); // Team ID: 1, Initial Supplies: 10
    initializeTeam(&team2, 2, 10); // Team ID: 2, Initial Supplies: 10

    // Create Zones
    int numZones = 5;
    Zone* zones[numZones];

    zones[0] = createZone(1, 1, 2, 5); // Zone ID: 1, Priority: 1, Supplies: 2, Total People: 5
    zones[1] = createZone(2, 2, 1, 6); // Zone ID: 2, Priority: 2, Supplies: 1, Total People: 6
    zones[2] = createZone(3, 1, 3, 4); // Zone ID: 3, Priority: 1, Supplies: 3, Total People: 4
    zones[3] = createZone(4, 3, 0, 7); // Zone ID: 4, Priority: 3, Supplies: 0, Total People: 7
    zones[4] = createZone(5, 2, 2, 5); // Zone ID: 5, Priority: 2, Supplies: 2, Total People: 5

    // Add People to Zones
    // Zone 1
    addPersonToZone(zones[0], createPerson("Alice", 0));
    addPersonToZone(zones[0], createPerson("Bob", 1));
    addPersonToZone(zones[0], createPerson("Charlie", 0));
    addPersonToZone(zones[0], createPerson("Diana", 1));
    addPersonToZone(zones[0], createPerson("Eve", 0));

    // Zone 2
    addPersonToZone(zones[1], createPerson("Frank", 0));
    addPersonToZone(zones[1], createPerson("Grace", 1));
    addPersonToZone(zones[1], createPerson("Hannah", 0));
    addPersonToZone(zones[1], createPerson("Ivan", 1));
    addPersonToZone(zones[1], createPerson("Judy", 0));
    addPersonToZone(zones[1], createPerson("Karl", 0));

    // Zone 3
    addPersonToZone(zones[2], createPerson("Leo", 0));
    addPersonToZone(zones[2], createPerson("Mona", 1));
    addPersonToZone(zones[2], createPerson("Niaj", 0));
    addPersonToZone(zones[2], createPerson("Olivia", 1));

    // Zone 4
    addPersonToZone(zones[3], createPerson("Paul", 0));
    addPersonToZone(zones[3], createPerson("Quentin", 0));
    addPersonToZone(zones[3], createPerson("Rupert", 1));
    addPersonToZone(zones[3], createPerson("Sybil", 0));
    addPersonToZone(zones[3], createPerson("Trent", 0));
    addPersonToZone(zones[3], createPerson("Uma", 1));
    addPersonToZone(zones[3], createPerson("Victor", 0));

    // Zone 5
    addPersonToZone(zones[4], createPerson("Walter", 0));
    addPersonToZone(zones[4], createPerson("Xena", 1));
    addPersonToZone(zones[4], createPerson("Yvonne", 0));
    addPersonToZone(zones[4], createPerson("Zara", 1));
    addPersonToZone(zones[4], createPerson("Aaron", 0));

    // Assign Zones to Teams Alternately
    for(int i = 0; i < numZones; i++) {
        if(i % 2 == 0) {
            enqueueZone(team1.pq, zones[i]);
        }
        else {
            enqueueZone(team2.pq, zones[i]);
        }
    }

    // Display Initial Zones and Team Status
    printf("\n=== Initial Team Status ===\n");
    displayTeam(&team1);
    displayTeam(&team2);
    printf("---------------------------------------\n");

    // Initialize Rescued Records BST
    RescuedRecord* rescueRecords = NULL;

    // Start Rescue Operations for Team 1
    printf("\n--- Team 1 Starting Operations ---\n");

    Zone* currentZone;
    while((currentZone = dequeueZone(team1.pq)) != NULL) {
        printf("\nProcessing Zone ID: %d, Priority: %d, Supplies: %d, Total People: %d, Rescued: %d\n", 
               currentZone->id, currentZone->priority, currentZone->supplies, 
               currentZone->totalPeople, currentZone->rescueCount);
        printf("Team 1 Supplies: %d\n", team1.supplies);

        // Calculate people needing rescue (only those without supplies)
        int peopleNeedingRescue = 0;
        Person* person = currentZone->people;
        while(person != NULL) {
            if(!person->isRescued && !person->hasSupplies) {
                peopleNeedingRescue++;
            }
            person = person->next;
        }
        printf("People needing rescue (without supplies): %d\n", peopleNeedingRescue);

        // Rescue people without supplies
        person = currentZone->people;
        while(person != NULL && team1.supplies > 0) {
            if(!person->isRescued && !person->hasSupplies) {
                person->isRescued = 1;
                team1.rescuedCount++;
                currentZone->rescueCount++;
                team1.supplies--;

                // Insert into rescued records
                rescueRecords = insertRescuedRecord(rescueRecords, person->name, currentZone->id);

                printf("Rescued %s from Zone %d.\n", person->name, currentZone->id);
            }
            person = person->next;
        }

        // Provide additional supplies if needed and possible
        if(team1.supplies > 0) {
            if(currentZone->supplies < (currentZone->totalPeople - currentZone->rescueCount)) {
                int needed = (currentZone->totalPeople - currentZone->rescueCount) - currentZone->supplies;
                provideSupplies(&team1, currentZone, needed);
            }
        }

        printf("---------------------------------------\n");
    }

    printf("\n--- Team 1 Completed Operations ---\n");

    // Start Rescue Operations for Team 2
    printf("\n--- Team 2 Starting Operations ---\n");

    while((currentZone = dequeueZone(team2.pq)) != NULL) {
        printf("\nProcessing Zone ID: %d, Priority: %d, Supplies: %d, Total People: %d, Rescued: %d\n", 
               currentZone->id, currentZone->priority, currentZone->supplies, 
               currentZone->totalPeople, currentZone->rescueCount);
        printf("Team 2 Supplies: %d\n", team2.supplies);

        // Calculate people needing rescue (only those without supplies)
        int peopleNeedingRescue = 0;
        Person* person = currentZone->people;
        while(person != NULL) {
            if(!person->isRescued && !person->hasSupplies) {
                peopleNeedingRescue++;
            }
            person = person->next;
        }
        printf("People needing rescue (without supplies): %d\n", peopleNeedingRescue);

        // Rescue people without supplies
        person = currentZone->people;
        while(person != NULL && team2.supplies > 0) {
            if(!person->isRescued && !person->hasSupplies) {
                person->isRescued = 1;
                team2.rescuedCount++;
                currentZone->rescueCount++;
                team2.supplies--;

                // Insert into rescued records
                rescueRecords = insertRescuedRecord(rescueRecords, person->name, currentZone->id);

                printf("Rescued %s from Zone %d.\n", person->name, currentZone->id);
            }
            person = person->next;
        }

        // Provide additional supplies if needed and possible
        if(team2.supplies > 0) {
            if(currentZone->supplies < (currentZone->totalPeople - currentZone->rescueCount)) {
                int needed = (currentZone->totalPeople - currentZone->rescueCount) - currentZone->supplies;
                provideSupplies(&team2, currentZone, needed);
            }
        }

        printf("---------------------------------------\n");
    }

    printf("\n--- Team 2 Completed Operations ---\n");

    // Display Final Rescued People
    displayRescuedPeople(rescueRecords);

    // Collect all zones for unrescued people display
    Zone* allZones[numZones];
    for(int i = 0; i < numZones; i++) {
        allZones[i] = zones[i];
    }

    // Display Unrescued People
    displayUnrescuedPeople(allZones, numZones);

    // Display Final Team Status
    printf("\n=== Final Team Status ===\n");
    displayTeam(&team1);
    displayTeam(&team2);
    printf("---------------------------------------\n");

    // Display Remaining Zones with People
    printf("=== Zones Remaining with People ===\n");
    for(int i = 0; i < numZones; i++) {
        int remaining = zones[i]->totalPeople - zones[i]->rescueCount;
        if(remaining > 0) {
            printf("Zone ID: %d, Priority: %d, Supplies: %d, Total People: %d, Rescued: %d\n", 
                   zones[i]->id, zones[i]->priority, zones[i]->supplies, 
                   zones[i]->totalPeople, zones[i]->rescueCount);
        }
    }
    printf("---------------------------------------\n");

    // Memory Cleanup
    freeRescuedRecords(rescueRecords);
    freeZones(zones, numZones);
    free(team1.pq);
    free(team2.pq);

    return 0;
}
