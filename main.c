#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME_LENGTH 50



int main() {
  int choice;

  while (1) {
    Product product;
    printf("======== BIENVENUE CY LIBRARY ========\n");
    printf(" ->  Choisissez votre mode  \n");
    printf("1. MODE GESTION \n");
    printf("2. MODE ACHAT \n");
    printf("3. QUITTER\n");
    printf(" Faites votre choix : ");
    scanf("%d", &choice);
    fflush(stdin);

    switch (choice) {
      case 1:
        management_mode();
        break;
      case 2:
        purchase_mode();
        break;
      case 3:
        printf(" ====== Merci de votre visite ====== \n");
        exit(0);
      default:
        printf("Choix invalide. Veuillez réessayer.\n");
    }

    printf("\n");
  }

  return 0;
}
