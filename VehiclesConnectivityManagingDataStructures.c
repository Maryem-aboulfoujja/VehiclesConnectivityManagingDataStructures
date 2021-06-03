#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define MAX 100

typedef struct node_{
    char name[20];
    double dis;
    struct node_* next;
  
}node;

typedef struct car_{
   int x, y;
    char name[20];
    node* h;
}car;


typedef struct{
     int destination;
     int source;
     double weight; 
}edge;


double compute_distance(car vtx1, car vtx2);
void add_in_ll(node**, node*);
void display_edges(void);
void display_adjacent_vehicles(char*);
int find_car(char*);
void add_vehicle(double, double, char*);
void delete_edge(char*, char*);
void delete_vehicle(char*);
void dfs( char* car_beg, int* visited);
void bfs(char* car_beg);
void add_edge(char* c1, char* c2);
bool already_linked (car, char*);
void move_car(char*, int, int);
void display_dij(int s, int d);
void djikstra (char* s, char* d);


car graph[MAX];
int n, range, ind_last;
double d;
double sum;
int path[MAX];
int visited[30];
int h = -1, rear = -1;
int queue[MAX];
edge T[MAX]; 
double distances[MAX];


int main(void) {
  int choice;
  double co1, co2;
  char ch_vehicle[20], keyboard_name[10], c1[10], c2[10], id_beg[20];
  int i, j, temp;
  FILE* fin = fopen("data.txt", "r");
  car *h, *rear;
  double dis;
  node* newnode;
  if(!fin){
    printf("FILE NOT FOUND!");
    return 0;
  }
  else{
    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &range);
    for(i = 0; i < n; i++){
      fscanf(fin, "%s",graph[i].name);
      fscanf(fin, "%d", &(graph[i].x));
      fscanf(fin, "%d", &(graph[i].y));
      graph[i].h =  NULL;
      ind_last = i;
      }
  }
  fclose(fin);
  for (i =0; i < n; i++){
    for(j =0; j < n; j++){
      dis = compute_distance(graph[i], graph[j]);
      if(!dis) continue;

      if (dis <= range){
        newnode = (node*)malloc(sizeof(node));
        newnode->dis = dis;
        newnode->next = NULL;
        strcpy(newnode->name, graph[j].name);
        add_in_ll(&(graph[i].h), newnode);
      }
    }
  }

  printf("Welcome dear user!\n");
do{
    printf("\nEnter:\n\t 1 to Display All Edges.\n\t 2 to Display Adjacent Vehicles.\n\t 3 to Add a Vehicle.\n\t 4 to Delete a Vehicle.\n\t 5 to Add an Edge.\n\t 6 to Delete an Edge.\n\t 7 to Move a Vehicle.\n\t 8 for DFS.\n\t 9 for BFS.\n\t 11 for Shortest Path between 2 vehicles.\n\t 12 to quit.\n Your choice: ");
    
    
    scanf("%d", &choice);

    switch(choice){
      case 1:
      printf("\nAll Edges:\n");
      display_edges();
        break;
      case 2:
      printf("\nEnter the car ID that you want to know its adjancency cars:\n");
      scanf("%s", ch_vehicle);
      printf("\nThe adjacent cars to %s are:\n", ch_vehicle);
      display_adjacent_vehicles(ch_vehicle);
        break;
      case 3:
      printf("Enter the name of the vehicle: ");
      scanf("%s", keyboard_name);
      if(find_car(keyboard_name) != 99){
      printf("This Id already exists!!\n");
      continue;
      }
      printf("Enter the x coordinate: ");
      scanf("%lf", &co1);
      printf("Enter the y coordinate: ");
      scanf("%lf", &co2);
      add_vehicle(co1, co2, keyboard_name);
      printf("Car successfully added!\n");
      break;
      case 4:
       printf("Enter the Id of the vehicle to delete: ");
       scanf("%s", keyboard_name);
       if(find_car(keyboard_name) == 99){
         printf("This car does not exist!\n");
       } else{
         delete_vehicle(keyboard_name);
         printf("Car successfully deleted!\n");
       }
        break;
      case 5:
       printf("Enter the Id of the first vehicle: ");
       scanf("%s", c1);
       printf("Enter the Id of the second vehicle: ");
       scanf("%s", c2);
       if(find_car(c1) == 99){
        printf("the Id %s does not exist!\n", c1);
      } else if(find_car(c2) == 99 ){
        printf("the Id %s does not exist!\n", c2);
      }else{
        add_edge(c1, c2);
      }
        break;
      case 6:
       printf("Enter the Id of the first car: ");
       scanf("%s", c1);
       printf("Enter the Id of the second car: ");
       scanf("%s", c2);
      if(find_car(c1) == 99){
        printf("the Id %s does not exist!\n", c1);

      } else if(find_car(c2) == 99 ){
        printf("the Id %s does not exist!\n", c2);
        }
      else{
        delete_edge(c1,c2);
        delete_edge(c2,c1);
      }
      printf("Edge successfully deleted!\n");
        break;
      case 7:
      printf("Enter the car Id:\n");
      scanf("%s", keyboard_name);
      printf("Enter the x-coordinate of the car:\n");
      scanf("%lf", &co1);
      printf("Enter the y-coordinate of the car:\n");
      scanf("%lf", &co2);
      if(find_car(keyboard_name) == 99){
          printf("The selected ID does not exist");
      }else{
        move_car(keyboard_name, co1, co2);
        printf("Car successfully Moved!");
      }
        break;
      case 8:
        printf("Enter the ID of the car that you want to start with: ");
        scanf("%s", id_beg);
        if(find_car(id_beg) == 99){
          printf("The selected ID does not exist");
        }
        else{
          printf("The DFS traversal of the graph is: ");
          dfs(id_beg, visited);
        }
        break;
      case 9:
       printf("Enter the ID of the car that you want to start with: ");
        scanf("%s", id_beg);
        if(find_car(id_beg) == 99){
          printf("The selected ID does not exist");
        }
        else{
          printf("The BFS traversal of the graph is: ");
          bfs(id_beg);
        }
        break;
      case 11:
      printf("Enter the name of the start vehicle:");
      scanf("%s", c1);
      printf("Enter the name of the destination vehicle: ");
      scanf("%s", c2);
      djikstra(c1,c2);
		  /*display_dij(find_car(c1),find_car(c2));
       printf(" The MIN DISTANCE is : %.2f \n",sum);
      */
        break;
      case 12:
        printf("Thank you for using our program!\n\n");
        return 0;
        break;
      
    }

}while(choice!=12);
  

  return 0;
}
     
    
void add_in_ll(node** head, node* _new){

  node* w;

  if(*head == NULL){
    *head = _new; 
    (*head)->next = NULL;
    return;
  }

  if(_new->dis < (*head)->dis){
    _new -> next = *head;
    *head = _new;
     return;
  }

  for(w = *head; w-> next != NULL; w=w->next){
    if(_new->dis< w->next->dis){
      _new->next = w->next;
       w->next = _new;
       break;
    } 
    
    }
    if (w->next == NULL){
    w->next = _new;
    }
  
}
double compute_distance(car vtx1, car vtx2){
  double d;
  d = sqrt(pow(vtx2.x - vtx1.x, 2) + pow(vtx2.y - vtx1.y, 2));
  return d;
}



  void display_edges(void){
    int i;
    node* w;
    for(i=0; i < n; i++){
      for(w = graph[i].h; w!= NULL; w=w->next){
          printf("(%s, %s, %.2f)\n", graph[i].name, w->name, w->dis);

      }
    }
  }

  void display_adjacent_vehicles(char* ch_vehicle){
    int i;
    node* w;
    i = find_car(ch_vehicle);
    if(i == 99) {
    printf("\nVehicle Not Found\n");
    return;
    }
      for(w=graph[i].h; w!=NULL; w=w->next){
          printf("%s ", w->name);
      }
      printf("\n");
    
  }



  int find_car(char* ch_vehicle){
    int i;
    for(i = 0; i<n; i++){
        if(!strcmp(graph[i].name, ch_vehicle))
        return i;
       }

      return 99;
  }
void add_vehicle(double co1, double co2, char* keyboard_name){
 
 
 int i,j; 
 double dis;
 node* newnode;
 ind_last++;
 strcpy(graph[ind_last].name, keyboard_name);
 graph[ind_last].x = co1;
 graph[ind_last].y = co2;
 graph[ind_last].h = NULL;
 n = n+1;
 
 
 for (i = 0; i <n; i++){
 dis = compute_distance(graph[ind_last], graph[i]);
 if(!dis) continue;
 if (dis <= range){
 newnode = (node*)malloc(sizeof(node));
 strcpy(newnode->name, graph[i].name);
 
 newnode->dis = dis;
 newnode->next = NULL;
 add_in_ll(&(graph[ind_last].h), newnode);
 
 }
 }
 
 for (i = 0; i < n - 1; i++){
 dis = compute_distance(graph[ind_last], graph[i]);
 if (dis <= range){
 newnode = (node*)malloc(sizeof(node));
 newnode->dis = dis;
 newnode->next = NULL;
 strcpy(newnode->name, graph[ind_last].name);
 add_in_ll(&(graph[i].h), newnode);
 }
 }
 return;
}
  

void delete_vehicle(char* v){
  int i;
  int ind = find_car(v);
  double distance;
  for(i = 0; i <= ind_last; i++){
    distance = compute_distance(graph[i], graph[ind]);
    if (distance <= range && distance != 0){
      delete_edge(v, graph[i].name);
      delete_edge(graph[i].name,v);
    }
    
  }

  for (i = ind; i < ind_last; i++){
    strcpy(graph[i].name, graph[i+1].name);
    graph[i].x = graph[i+1].x;
    graph[i].y = graph[i+1].y;
    graph[i].h = graph[i+1].h;    
  }
  n = n - 1;
  ind_last = ind_last - 1;

}

void delete_edge(char* car1, char* car2){
  int key1 = find_car(car1);
  int key2 = find_car(car2);
  int i;
  node* w, *found;
  for(i =  0; i < n; i++){
    if(!strcmp(graph[key1].h->name, car2)){
      found = graph[key1].h;
      graph[key1].h = graph[key1].h->next;
      found->next= NULL;
      free(found);
      return;
    }
    for(w=graph[key1].h; w->next != NULL; w=w->next){
      if (!strcmp(w->next->name, car2)){
        found = w->next;
        w->next = found->next;
        found->next = NULL;
        free(found);
        return;

      }
    }
  }
  return;
}
void dfs( char* car_beg, int* visited){
  node* w;
  int index;
  index = find_car(car_beg);
  visited[index] = 1;
  printf("%s ", graph[index].name);
  for(w = graph[index].h; w != NULL; w=w->next){
    index = find_car(w->name);
    if(!visited[index]){
      dfs(w->name, visited);
    }
  }

}

void bfs(char* car_beg){
  int i, visited[MAX];
  int id, temp, temp1;
  node* w;;
  id= find_car(car_beg);
  for(i=  0; i < MAX; i++){
    visited[i] = 0;
  }
  printf("%s ", graph[id].name);
  visited[id] = 1;
  if(h == -1){
    h = 0;
  }
  rear = rear + 1;
  queue[rear] = id;
    while(!(h>rear)){
      temp = queue[h];
      h = h+1;
     for(w = graph[temp].h; w!=NULL; w = w->next){
       temp1 = find_car(w->name);
       if(!visited[temp1]){
         printf("%s ", graph[temp1].name);
         if(h == -1){
            h = 0;
         }
         rear = rear + 1;
         queue[rear] = temp1;
         visited[temp1] = 1;
       }

     }
    }

}


void add_edge(char* c1, char* c2){
  int i;
  int id1 = find_car(c1);
  int id2 = find_car(c2);
  double d = compute_distance( graph[id1], graph[id2]);
  node* newnode;
  if (d <= range){
    /*if(already_linked(graph[id1], c2)){
      printf("There is already an edge between %s and %s!\n", c1, c2);
      return;
    }*/
  newnode = (node*)malloc(sizeof(node));
  newnode->dis = d;
  newnode->next = NULL;
  strcpy(newnode->name, graph[id2].name);
  add_in_ll(&(graph[id1].h), newnode);
  newnode = (node*)malloc(sizeof(node));
  newnode->dis = d;
  newnode->next = NULL;
  strcpy(newnode->name, graph[id1].name);
  add_in_ll(&(graph[id2].h), newnode);
  printf("Edge successfully added!\n");
  return;

  } 
    printf("\nOops, could not add an edge! The distance between %s and %s is beyond the given range!\n", graph[id1].name, graph[id2].name);
  return;
  
 }

bool already_linked (car elt, char* wanted){
   node* w;
   for(w=elt.h; w!=NULL; w=w->next){
     if(!strcmp(w->name, wanted)){
        return true;
     }
   }
   return false;

} 
void move_car(char* Id, int co1, int co2){
    delete_vehicle(Id);
    add_vehicle(co1, co2, Id);
}

void djikstra(char* s, char* d){
    int i, min_i;
    int i_s = find_car(s), i_d = find_car(d);
    node *w1,*w2;
  
    for(i = 0;i < MAX; i++){
       distances[i]=9999;
       path[i]= -1;
       visited[i]=0;
    }
    int flag = 0;
    for (i = 0; i < n; i++){
      if(already_linked (graph[i], d)){
        flag = 1;
    }
    }
    if(!flag) {
      printf("There is no path from %s to %s\n", s, d);
      return;
    }

    visited[i_s]=1;
    distances[i_s]=0;

    for(w1 = graph[i_s].h;w1 != NULL;w1 = w1->next){
        distances[find_car(w1->name)]= w1->dis;
        path[find_car(w1->name)]=i_s; 
    }
     do{
       int m=9999;
       for(i = 0; i < MAX; i++)
            if(visited[i]==0 && distances[i] < m) {
                m = distances[i];
                min_i = i;
               }
        visited[min_i]=1;
        
            for(w2=graph[min_i].h; w2!=NULL;w2=w2->next){
                if(visited[find_car(w2->name)]==0 && ( (distances[min_i] + compute_distance(graph[min_i],graph[find_car(w2->name)] ) ) < distances[find_car(w2->name)]))
                {
                distances[find_car(w2->name)] = distances[min_i] + compute_distance(graph[min_i],graph[find_car(w2->name)] );
                 path[find_car(w2->name)] = min_i;
                }
            }  
        }while(!visited[i_d]);
        printf("\n***** The Dijkstra path from %s to %s ****\n",graph[i_s].name,graph[i_d].name);
       display_dij(i_s, i_d);
       printf(" The MIN DISTANCE is : %.2f \n",sum);
      
}
void display_dij( int s,int d){
  int t;
  
    if (s==d)
      return;
    else{
        t=path[d];
        display_dij(s,t);
        printf(" %s to %s\n",graph[t].name,graph[d].name);
        sum +=  compute_distance(graph[d],graph[t]);
        }
}