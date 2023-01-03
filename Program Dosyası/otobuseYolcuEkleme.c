#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 5
#define MAX_SEATS 5

// Yolcu bilgilerini tutan yapı
typedef struct passenger_node {
char name[50];
char surname[50];
int seat;
struct passenger_node *next;
} passenger_node;

// Otobüs bilgilerini tutan yapı
typedef struct {
passenger_node *passengers;
int current_seat;
} bus;

// Stack yapısını kullanarak otobüsleri tutan yapı
typedef struct {
bus buses[MAX_BUSES];
int top;
} bus_stack;

// Otobüs ekleme fonksiyonu
void push_bus(bus_stack *stack, bus new_bus) {
if (stack->top == MAX_BUSES - 1) {
printf("Error: Maksimum otobus sayisina ulastiniz.\n");
return;
}

stack->buses[++stack->top] = new_bus;
}

// Otobüs çıkarma fonksiyonu
bus pop_bus(bus_stack *stack) {
if (stack->top == -1) {
printf("Error: Stack'ta otobus yok.\n");
exit(1);
}

return stack->buses[stack->top--];
}

// Yolcu ekleme fonksiyonu
void add_passenger(bus *current_bus, passenger_node *new_passenger) {
if (current_bus->current_seat == MAX_SEATS) {
printf("Error: Maksimum koltuk sayisina ulastiniz.\n");
return;
}

// Yolcu listesi boşsa yeni yolcu ilk eleman olsun
if (current_bus->passengers == NULL) {
current_bus->passengers = new_passenger;
} else {
// Yolcu listesinin sonuna yolcu ekle
passenger_node *current = current_bus->passengers;
while (current->next != NULL) {
current = current->next;
}
current->next = new_passenger;
}

current_bus->current_seat++;
}

// Otobüsleri ekrana yazdırma fonksiyonu
void print_buses(bus_stack buses) {
for (int i = 0; i <= buses.top; i++) {
printf("\n******************* %d.Otobus *******************\n", i + 1);
passenger_node *current = buses.buses[i].passengers;
for (int j = 0; j < MAX_SEATS; j++) {
printf("%d nolu yolcu - Yolcu Adi : %s - Yolcu Soyadi : %s\n", j + 1, current->name, current->surname);
current = current->next;
}
}
}

int main() {
// İlk otobüsü oluştur
bus current_bus;
current_bus.current_seat = 0;
current_bus.passengers = NULL;

// Otobüsleri tutan stack yapısını oluştur
bus_stack buses;
buses.top = -1;

// Yolcu ekleme işlemini kullanıcıdan alma
char choice;
do {
passenger_node *current_passenger = (passenger_node*) malloc(sizeof(passenger_node));
printf("Yolcu ismini girin: ");
scanf("%s", current_passenger->name);
printf("Yolcu soyadini: ");
scanf("%s", current_passenger->surname);
printf("Koltuk numarasini girin(Max 5): ");
scanf("%d", &current_passenger->seat);
current_passenger->next = NULL;

// Yolcuyu otobüse ekle
add_passenger(&current_bus, current_passenger);

// Otobüs dolduysa yeni otobüs ekle
if (current_bus.current_seat == MAX_SEATS) {
  push_bus(&buses, current_bus);
  current_bus.current_seat = 0;
  current_bus.passengers = NULL;
}
printf("Devam etmek istiyorsaniz 'y', cikmak istiyorsaniz 'n' giriniz! \n");
scanf(" %c", &choice);
} while (choice == 'y' || choice == 'Y');

// Eğer otobüste kalan yolcu varsa stack'e ekle
if (current_bus.current_seat > 0) {
push_bus(&buses, current_bus);
}

// Tüm otobüsleri ekrana yazdır
print_buses(buses);

return 0;
}




