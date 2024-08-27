#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

struct node {
    int num;
    struct node* nextptr;
};

struct node *arr[1024];                //1024 is the maximum of linked lists that we could have ( 2^10 )

typedef int galois;                   //typedef uint8_t galois; 
                                      //polynomials for each n ( 1 <=n <=10 )
const galois polynomial2  = 0b111;
const galois polynomial3  = 0b1101;
const galois polynomial4  = 0b11001;
const galois polynomial5  = 0b101001;
const galois polynomial6  = 0b1100001;
const galois polynomial7  = 0b11000001;
const galois polynomial8  = 0b101001101;
const galois polynomial9  = 0b1100010101;
const galois polynomial10 = 0b10010000001;


const int generator = 0b10;            // Generator of Galois field 



void createNodeList(int n);
void addtoList(int a,int n,int cnt);
void displayList();


void add(int add1,int add2,int n);
void multi(int add3,int add4,int n,int gen);

int elements2(int a,int gen);
int elements3(int a,int gen);
int elements4(int a,int gen);
int elements5(int a,int gen);
int elements6(int a,int gen);
int elements7(int a,int gen);
int elements8(int a,int gen);
int elements9(int a,int gen);
int elements10(int a,int gen);

int main (void)
{
 int n;
 
 printf("Give an integer between the space: [1,10]\n");

 for(int i = 0;i<1;i++){
    scanf("%d",&n);
     if(n < 1 || n > 10){
       printf("False! n should be in space [1,10]. Try again\n");
       i--;
       continue;     
     }
  }
    
  createNodeList(n);

  int a = 0;           //elements
  int counter = 0;     //in order to know in which linked list we are gonna put our elements next 
    
 for(int i = 0; i < pow(2,n);i++){      
     addtoList(a,n,counter);

      if(a==0){
        a = 1;
        counter++;
        continue;       
       }

      if(n==2)
        a = elements2(a,generator);

      if(n==3)
        a = elements3(a,generator);

      if(n==4)
        a = elements4(a,generator);

      if(n==5)
        a = elements5(a,generator);

       if(n==6)
        a = elements6(a,generator);

       if(n==7)
        a = elements7(a,generator);

       if(n==8)
        a = elements8(a,generator);

       if(n==9)
        a = elements9(a,generator);

       if(n==10)
        a = elements10(a,generator);
  
        counter++;     
}

  displayList(n);

  char order1 = '+';
  char order2 = '*';
  char order3[10] = "exit\n";
  char order[15];
  char *v;
  char Zechorder[15] = "Zech method\n";
  char Zech[10];
  v = (char*)malloc(sizeof(char)*10);
  char orderc;

 getchar();


  for(int i = 0;i<1;i++)
 {
    int count1 = 0;
    int count2 = 0;
     
    printf("\n\nOption 1: x+y\nOption 2: x*y\nOption 3:exit\nOption 4:Zech method\n");

    fgets(order,sizeof(order),stdin);

    if(strcmp(order,"exit")!=0 && strcmp(order,"Zech method")!=0){    //seeing if the input is '+' or '*'
         for(int i = 0;i<sizeof(order)/4;i++){
            if(order[i] == '+'){
             count1++;
            }

            if(order[i] == '*'){
             count2++;
            }
         }
    }
   
    if(strcmp(order,order3)==0){             //exit order
       printf("The Program has been terminated");
       exit(1);
     }

       
    if(count1==1 && count2==0){              //+ order
        v = strtok(order,"+");
        int add1,add2;
        add1 = atoi(v);

        v = strtok(NULL,"+");
        add2 = atoi(v);

        if(add1==add2){
         struct node *tmp;
         tmp = arr[0];
         while(tmp!=NULL){
           printf("%d",tmp->num);
           tmp = tmp->nextptr;             
         }
         i--;
         continue;
     }

     add(add1,add2,n);
           
     i--;
     continue;      
   }

   if(count2==1 && count1==0){ //* order
      v = strtok(order,"*");
      int add3,add4;
      add3 = atoi(v);

      v = strtok(NULL,"*");
      add4 = atoi(v);

      multi(add3,add4,n,generator);
      i--;
      continue;
    }

               

    if(strcmp(Zechorder,order) == 0){  //addition using the Zech method
       int p,q = 0;
       fgets(Zech,sizeof(Zech),stdin);
       v = strtok(Zech,"+"); //first number
       p = atoi(v);
                      
       v = strtok(NULL,"+"); //second number
       q = atoi(v);

        if(p-q<0){
        }

        if(p-q>0){      
         int temporary = p;
         p = q;
         q = temporary;                    
        }

        if(p-q==0){
         struct node *tempor;
         tempor = arr[0];
         while(tempor!=NULL){
            printf("%d",tempor->num);
            tempor = tempor->nextptr;
          }
          i--;
          continue;
         }
    
                          //calculation Z(q-p) 
                          //α^p+a^q = a^p*a^Z(q-p) για p<q και
                          //α^p+a^q = a^q*a^Z(p-q) για p>q
        struct node *tmp;
        int log = q-p;
        int cop[n];
        int ctr = 0;
        int bin = 0;
        printf("%d",log);
   
        tmp = arr[q-p+1];
                            // saving the binary number a^q-p  in an array of integers
        while(tmp!=NULL){
         cop[ctr] = tmp->num;
         tmp = tmp->nextptr;   
         ctr++;
         }
        
        ctr = 0;      //reseting the counter
                                      
        int bits,c1;  //saving the binary number into an integer
        for(int i = 0;i<n;i++){
           if(i==0){
            c1 = cop[i];
            continue;
           }
           bits = cop[i]<<i;
           c1 += bits;
        }
                                  
        int z = c1^1;  //a^Z(q-p) = z
                                         

                       //Z(q-p) = ;
                       //Convert demical to binary
        int az[n];
        for(int i=0;i<n;i++){  //z>0  
          az[i]=z%2;
          z=z/2;
        }

        int counter3=0;
        int m = 0;
        for(m = 0;m<pow(2,n);m++){
                                          
          tmp = arr[m];
          for(int j = 0;j<n;j++){
            if(az[j]==tmp->num){                                          
              counter3++;
              tmp = tmp->nextptr;
            } 
                                           
            else {
              counter3 = 0;
              break;
            }
        }
            
        if(counter3==n)
         break;

    }
 
    int power = m-1; // Z(q-p) = power -> a^power
                     //printf("\n%d\n%d\n",i,power);
           
                     //a^p in binary
    tmp = arr[p+1]; 
    ctr = 0;
    while(tmp!=NULL){
      cop[ctr] = tmp->num;
      tmp = tmp->nextptr;
      ctr++;
    }

    bits = 0;                                        
    c1 = 0;
    for(int i = 0;i<n;i++){

        if(i==0){
          c1 = cop[i];
          continue;
        }

        bits = cop[i]<<i;
        c1 += bits;
     }

     for(int i = 0; i < power;i++){ //Now we are implementing the a^(p+Z(q-p))
         
         if(n==2)
           c1 = elements2(c1,generator);

         if(n==3)
            c1 = elements3(c1,generator);

         if(n==4)
            c1 = elements4(c1,generator);

         if(n==5)
            c1 = elements5(c1,generator);

         if(n==6)
            c1 = elements6(c1,generator);

         if(n==7)
            c1 = elements7(c1,generator);

         if(n==8)
            c1 = elements8(c1,generator);

         if(n==9)
            c1 = elements9(c1,generator);

         if(n==10)
            c1 = elements10(c1,generator);

        }
       
        int az2[n];
        for(int i=0;i<n;i++){  //z>0                                        
          az2[i]=c1%2;
          c1=c1/2;
        }
         
        for(int i = n-1;i>-1;i--) //result
          printf("%d",az2[i]);
                                                                         
        i--;
        continue;                //calling menu again                                     

    }

          
        if(count1==0 && count2==0 && strcmp(order3,order)!=0 && strcmp(order,Zechorder)!=0){
           printf("No such an order found\n");
           i--;
           continue;
         } 

          
  }

return 0;
}


void createNodeList(int n)
{
    struct node *fnNode, *tmp ,*stnode;
    int num, i;

    for(int i = 0;i < pow(2,n);i++ ){
      stnode = (struct node *)malloc(sizeof(struct node));
      arr[i] = stnode;

      if(stnode == NULL){ //check whether the fnnode is NULL and if so no memory allocation
        printf(" Memory can not be allocated.");
        exit(1);
      }
      else{
        // reads data for the node through keyboard
        stnode->nextptr = NULL;
        tmp = stnode;
        // Creating n nodes and adding to linked list
        for(int i=2; i<=n; i++){
            fnNode = (struct node *)malloc(sizeof(struct node));
            if(fnNode == NULL){
                printf(" Memory can not be allocated.");
                break;
            }
            else{              
                fnNode->nextptr = NULL;  // links the address field of fnNode with NULL
                tmp->nextptr = fnNode;   // links previous node i.e. tmp to the fnNode
                tmp = tmp->nextptr; 
            }
         }
      }
   }

} 

void displayList(int n)
{
 struct node *tmp;
 int arr2[n];            //saving bits inside an array
 int j = 0;              //counter in order to acknowledge each position of the bit

  for(int i = 0;i < pow(2,n);i++){
     tmp = arr[i];  
     while(tmp != NULL){
        arr2[j] = tmp->num;
        //printf(" Data = %d\n", tmp->num);       // prints the data of current node
        tmp = tmp->nextptr;
        j++;                                     
     }
     j=0;

     for(int b = n-1;b > -1;b--){
      printf("%d",arr2[b]);
     }        
     printf("\n");   
  }
} 


void addtoList(int a,int n,int cnt)
{
   struct node *tmp;
   tmp = arr[cnt];

   for(int i=0;i < n ;i++){    
    tmp->num = a%2;
    // printf("%d",tmp->num);
    tmp = tmp->nextptr;
    //arr[i]=a%2;    
    a=a/2;    
  }    
// printf("\n");
}

void add(int add1,int add2,int n)
{
    struct node *tmp;
    int c1,c2 = 0;
    int binary[n];
    int counter = 0;
    tmp = arr[add1+1];  //We are looking to the power a^add1 that user gave us

     //We are saving the binary number into an array and then we are gonna convert it into demical in order to do the ^
    //1st power
    while(tmp != NULL){  
     binary[counter] = tmp->num; 
     tmp = tmp->nextptr;
     counter++;
    }

    int bits;   
    for(int i = 0;i<n;i++){
     if(i==0){
      c1 = binary[i];
      continue;
     }
     bits = binary[i]<<i;
     c1 += bits; 
    }   
                       //Same process
    tmp = arr[add2+1]; //We are looking to the number that user wanted to add to add1
    counter = 0;
    //2nd power
    while(tmp != NULL){
     binary[counter] = tmp->num;
     tmp = tmp->nextptr;
     counter++;
    }

     int bits2;
     for(int i = 0;i<n;i++){
        if(i==0){
         c2 = binary[i];
         continue;
      }

      bits2 = binary[i]<<i;
      c2 += bits2;
     }

     int result;
     result = c1^c2;
           
     //Convert demical to binary
     int a[n];
     for(int i=0;i<n;i++){  //result>0      
        a[i]=result%2;    
        result=result/2;    
      }    
    
      for(int i = n-1;i>-1;i--)
         printf("%d",a[i]);         
 
      //Finding the power of the result inside our linked list
      //our result is inside the a  array, wrote in binary. We are comparing the elemts of array a with the elements of our linked lists
      for(int i = 0;i<pow(2,n);i++){
         int cnt = 0;
         tmp = arr[i];
         while(tmp != NULL){
             if(a[cnt] == tmp->num){
              cnt++;
              tmp = tmp->nextptr;
              }

             else
              break;
          }

          if(cnt == n){
              printf("\npower: %d",i-1);
              break;
          }
      }          
}

void multi (int add3,int add4,int n,int gen)
{
   int res = 0;
   int binary[n];
   struct node *tmp;
   int counter = 0;
   int c1 = 0;

   tmp = arr[add3+1];

    while(tmp != NULL){
     binary[counter] = tmp->num;
     tmp = tmp->nextptr;
     counter++;
   }

   int bits;
   for(int i = 0;i<n;i++){
      if(i==0){
       c1 = binary[i];
       continue;
      }

      bits = binary[i]<<i;
      c1 += bits;
    }

   printf("%d\n",c1);
   for(int i = 0;i<add4;i++){

       if(n==2)
        c1 = elements2(c1,generator);

        if(n==3)
         c1 = elements3(c1,generator);

        if(n==4)
         c1 = elements4(c1,generator);

        if(n==5)
         c1 = elements5(c1,generator);

        if(n==6)
         c1 = elements6(c1,generator);

        if(n==7)
         c1 = elements7(c1,generator);

        if(n==8)
         c1 = elements8(c1,generator);

        if(n==9)
         c1 = elements9(c1,generator);

        if(n==10)
         c1 = elements10(c1,generator);
   }
   

    //Convert res (which is demical) to binary
    int a[n];
    for(int i=0;i<n;i++){  //result>0      
        a[i]=c1%2;
        c1=c1/2;
     }

     for(int i = n-1;i>-1;i--)
        printf("%d",a[i]);

     //Power 
     for(int i = 0;i<pow(2,n);i++){
        int cnt = 0;
        tmp = arr[i];
        while(tmp != NULL){
        if(a[cnt] == tmp->num){
          cnt++;
        tmp = tmp->nextptr;
        }
         else
         break;
     }

     if(cnt == n){
        printf("\npower: %d",i-1);
        break;
     } 
   }
}

int elements2(int a,int gen)
{
  int res = 0;

  for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 10)
            a = (a << 1) ^ polynomial2;
        else
            a <<= 1;
  }

    return res;
}

int elements3(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 100)
            a = (a << 1) ^ polynomial3;
        else
            a <<= 1;
    }

    return res;
}

int elements4(int a,int gen)
{
   int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 1000)
            a = (a << 1) ^ polynomial4;
        else
            a <<= 1;
    }

    return res;
}

int elements5(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 10000)
            a = (a << 1) ^ polynomial5;
        else
            a <<= 1;
    }

    return res;
}

int elements6(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 100000)
            a = (a << 1) ^ polynomial6;
        else
            a <<= 1;
    }

    return res;
}

int elements7(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 1000000)
            a = (a << 1) ^ polynomial7;
        else
            a <<= 1;
    }

    return res;
}

int elements8(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 10000000)
            a = (a << 1) ^ polynomial8;
        else
            a <<= 1;
    }

    return res;
}

int elements9(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 100000000)
            a = (a << 1) ^ polynomial9;
        else
            a <<= 1;
    }

    return res;
}

int elements10(int a,int gen)
{
    int res = 0;

    for (; gen; gen >>= 1) {
        if (gen & 1)
            res ^= a;
        if (a & 1000000000)
            a = (a << 1) ^ polynomial10;
        else
            a <<= 1;
    }

    return res;
}

