#include<stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct Task{
    int id;
    char title[100];
    int Priority;
    char Deadline[100];

}Task;
typedef struct ListTask{
    Task task;
    struct ListTask* next;
}ListTask;
typedef struct HistoryTask{
    Task task;
    struct HistoryTask* next;
    struct HistoryTask* prev;
}HistoryTask;

void printMenu(){
    printf("1. Them moi nhiem vu \n");
    printf("2. Hien thi nhiem vu \n");
    printf("3. Xoa nhiem vu \n");
    printf("4. Cap nhat nhiem vu \n");
    printf("5. Danh dau nhiem vu da hoan thanh\n");
    printf("6. Sap xep nhiem vu \n");
    printf("7. tim kiem nhiem vu \n");
    printf("8. Thoat\n");
    printf("Nhap lua chon cua ban : ");
    }
ListTask* createListTask(ListTask* head) {
    Task newTask;
    printf("Moi ban nhap id nhiem vu : ");
    scanf("%d", &newTask.id);
    getchar();
    printf("Moi ban nhap ten nhiem vu : ");
    fgets(newTask.title, 100, stdin);
    newTask.title[strcspn(newTask.title, "\n")] = '\0';
    printf("Moi an nhap do uu tien : ");
    scanf("%d", &newTask.Priority);
    getchar();
    printf("Moi ban nhap thoi gian hoan thanh : ");
    fgets(newTask.Deadline, 100, stdin);
    newTask.Deadline[strcspn(newTask.Deadline, "\n")] = '\0';
    ListTask* newListTask = (ListTask*)malloc(sizeof(ListTask));
    newListTask->task = newTask;
    newListTask->next = NULL;
    if (head == NULL) {
        printf("Them thanh cong \n");
        return newListTask;
    }
    ListTask* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newListTask;
    printf("Them thanh cong \n");
    return head;
}
void printListTask(ListTask* head) {
    ListTask* temp = head;
    while (temp != NULL) {
        printf("ID: %d || Title: %s || Priority: %d || Deadline : %s \n",temp->task.id,temp->task.title,temp->task.Priority,temp->task.Deadline);

        temp = temp->next;
    }

}
ListTask* delListTask(ListTask* head,int id) {
    if (head == NULL) {
        printf("Empty List");
    }
    if (head->task.id == id ) {
        ListTask* delTask = head;
        head = head->next;
        free(delTask);
        return head;

    }
    ListTask* temp = head;
    while (temp->next != NULL && temp->next->task.id != id) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("ko co nhiem vu can xoa \n");
        return head;
    }
    ListTask* delTask = temp->next;
    temp->next = delTask->next;
    free(delTask);
    printf("Xoa  thanh cong \n");
    return head;

}
ListTask* updateListTask(ListTask* head, int id) {
    if (head == NULL) {
        printf("Empty List");
    }
    if (head->task.id == id ) {

        printf("Moi ban nhap ten nhiem vu : ");
        fgets(head->task.title, 100, stdin);
        head->task.title[strcspn(head->task.title, "\n")] = '\0';
        printf("Moi an nhap do uu tien : ");
        scanf("%d", &head->task.Priority);
        getchar();
        printf("Moi ban nhap thoi gian hoan thanh : ");
        fgets(head->task.Deadline, 100, stdin);
        head->task.Deadline[strcspn(head->task.Deadline, "\n")] = '\0';
        return head;
    }
    ListTask* temp = head;
    while (temp->next != NULL && temp->next->task.id != id) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("ko co nhiem vu can sua \n");
    }
    printf("Moi ban nhap ten nhiem vu : ");
    fgets(temp->next->task.title, 100, stdin);
    temp->next->task.title[strcspn(temp->next->task.title, "\n")] = '\0';
    printf("Moi an nhap do uu tien : ");
    scanf("%d", &temp->next->task.Priority);
    getchar();
    printf("Moi ban nhap thoi gian hoan thanh : ");
    fgets(temp->next->task.Deadline, 100, stdin);
    temp->next->task.Deadline[strcspn(temp->next->task.Deadline, "\n")] = '\0';
    return temp->next;
}
ListTask* sortListTask(ListTask* head) {
    if (head == NULL) {
        printf("Empty List");
        return head;
    }
    ListTask *i,*j;
    for (i = head; i != NULL; i=i->next) {
        for (j = i->next; j != NULL; j=j->next) {
            if (i->task.Priority > j->task.Priority) {
                Task temp =i->task;
                i->task = j->task;
                j->task = temp;

            }
        }
    }
    printf("Sap xep thanh cong \n");
    return head;


}
void searchListTask(ListTask* head,char name[100]) {
    int found = 0;
    if (head == NULL) {
        printf("Empty List");
    }
    ListTask* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->task.title, name) == 0) {
            printf("ID: %d || Title: %s || Priority: %d || Deadline : %s \n",temp->task.id,temp->task.title,temp->task.Priority,temp->task.Deadline);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("khong co nhiem vu ban can tim \n");
    }

}
int main(){
    int choice;
    int id;
    char name[100];
    ListTask* head = NULL;
    do {
        printMenu();

        scanf("%d",&choice);
        getchar();
        switch(choice) {
            case 1:
                    head = createListTask(head);
                break;
            case 2:
                    printListTask(head);
                break;
            case 3:
                printf("Moi ban nhap id can xoa : ");
                scanf("%d",&id);
                getchar();
                head = delListTask(head,id);
                break;
            case 4:
                printf("Moi ban nhap id can sua: ");
                scanf("%d",&id);
                getchar();
                updateListTask(head,id);
                break;
            case 5:

                break;
            case 6:
                head = sortListTask(head);
                break;
            case 7:
                printf("Moi ban nhap ten nhiem vu can tim : ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                searchListTask(head,name);
                break;

            default:
                printf("Moi ban  nhap lai ");
                break;
        }

    }while (choice!=8);
    return 0;
}
