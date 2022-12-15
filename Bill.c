#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct items{
    char item[20];
    int qty;
    float price;
};
struct customer_details{
    char customer[20];
    char date[40];
    int numOfItems;
    struct items itm[20];
};
void generateBillHeader(char name[20], char date[30]){
    printf("\n\n");
    printf("\t\t\t\t\tA To Z Grocery");
    printf("\n\t\t\t\t*****************************");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("****************************************\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n****************************************");
    printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price){
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty*price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total - dis;
    float cgst = 0.09*netTotal, grandTotal = netTotal + 2*cgst;
    printf("****************************************\n");
    printf("Sub Total\t\t\t%0.2f", total);
    printf("\nDiscount @10\t\t\t%0.2f", dis);
    printf("\n\t\t\t*****");
    printf("\nNet Total\t\t\t%0.2f", netTotal);
    printf("\nCGST@9\t\t\t\t%0.2f", cgst);
    printf("\nSGST@9\t\t\t\t%0.2f", cgst);
    printf("\n****************************************\n");
    printf("\nGrand Total\t\t\t%0.2f", grandTotal);
    printf("\n****************************************\n");
}
int main(){
    int n;
    int choice;
    char name[20];
    int total = 0;
    int invoiceFound = 0;
    char saveBill = 'y';
    struct customer_details cust2;
    FILE *fp;
    first:
    printf("\n\n\t\t\t==========A To Z Grocery==========");
    printf("\n\n");
    printf("\n1.Generate Bill");
    printf("\n2.Show all the Bills");
    printf("\n3.Search existing Bill");
    printf("\n4.Exit");
    printf("\n");
    printf("\nPlease select your choice: ");
    scanf("%d", &choice);
    printf("You have selected option %d", choice);
    struct customer_details cust;
    fgetc(stdin);
    switch(choice){
        case 1:
        system("clear");
        printf("\nPlease enter name of the customer: ");
        fgets(cust.customer, 20, stdin);
        cust.customer[strlen(cust.customer-1)] = 0;
        strcpy(cust.date,__DATE__);
        printf("\nPlease enter the number of items: ");
        scanf("%d", &n);
        cust.numOfItems = n;
        for(int i=0; i<n; i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d: ", i+1);
            fgets(cust.itm[i].item, 20, stdin);
            cust.itm[i].item[strlen(cust.itm[i].item)-1] = 0;
            printf("Please enter the quantity: ");
            scanf("%d", &cust.itm[i].qty);
            printf("\nPlease enter the unit price: ");
            scanf("%f", &cust.itm[i].price);
            total += cust.itm[i].qty * cust.itm[i].price;

        }
        generateBillHeader(cust.customer, cust.date);
        for(int i=0; i<cust.numOfItems; i++){
            generateBillBody(cust.itm[i].item, cust.itm[i].qty, cust.itm[i].price);
        }
        generateBillFooter(total);
        printf("\n\n");
        printf("\nDo you want to save the customer details[y/n]: ");
        scanf("%s", &saveBill);
        if(saveBill == 'y'){
               fp = fopen("groceryBill.dat","a+");
               fwrite(&cust, sizeof(struct customer_details), 1, fp);
               if(fwrite!=0){
                printf("\nyour bill was saved successfully");
               }
               else{
                printf("Something Error");
               }
               fclose(fp);
        }
        goto first;
        break;
        case 2:
        system("clear");
        fp = fopen("groceryBill.dat", "r");
        printf("\n**********Your Previous Bills**********\n");
        while(fread(&cust, sizeof(struct customer_details), 1, fp)){
            generateBillHeader(cust2.customer, cust2.date);
            float total2 = 0;
            for(int i=0; i<cust.numOfItems; i++){
                generateBillBody(cust.itm[i].item, cust.itm[i].qty, cust2.itm[i].price);
                total2 += cust.itm[i].qty * cust.itm[i].price;
            }
            generateBillFooter(total2);
            printf("\n\n");
        }
        fclose(fp);
        goto first;
        break;
        case 3:
        printf("\nEnter the name of the customer to be searched: ");
        fgetc(stdin);
        fgets(name, 20, stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("groceryBill.dat", "r");
        printf("\n==========Invoice of %s==========", name);
        while(fread(&cust2, sizeof(struct customer_details), 1, fp)){
            float total2 = 0;
        if(!strcmp(cust2.customer, name)){
                generateBillHeader(cust2.customer, cust2.date);
                for(int i=0; i<cust2.numOfItems; i++){
                    generateBillBody(cust2.itm[i].item, cust2.itm[i].qty, cust2.itm[i].price);
                    total2 += cust2.itm[i].qty * cust2.itm[i].price; 
                }
                generateBillFooter(total2);
                invoiceFound = 1;
            }
        }
        if(!invoiceFound){
            printf("\nThe invoice for %s does not exist!", name);
        }
        goto first;
        break;
        case 4:
        printf("\n\n\nBye Bye!Thank You for using our Software.");
        exit(0);
        break;
        default:
        printf("\nPlease insert correct option");
        goto first;
        break;
    }
    return 0;
}
