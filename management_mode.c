#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_HISTO 500
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME_LENGTH 50


void management_mode() {
  int choice;
  Product products[MAX_PRODUCTS];
  int numProducts = 0;
  int totalSpace = 500;

  do {
    printf("======== MODE GESTION =======:\n");
    printf("====== CY LIBRARY GESTION ======:\n");
    printf("1. Ajouter un produit\n");
    printf("2. Modifier un produit\n");
    printf("3. Supprimer un produit\n");
    printf("4. Afficher tous les produits\n");
    printf("5. Afficher un produit par référence\n");
    printf("6. Afficher un produit par nom\n");
    printf("7. Augmenter le stock d'un produit\n");
    printf("8. Mode Gestion des stocks\n");
    printf("9. Quitter\n");
    printf("Faites votre choix : ");
    scanf("%d", &choice);
    vider_buffer();

    switch (choice) {
    case 1: {
      Product p;
      add_product(&p);
      break;
    }
    case 2: {
      int ref;
      printf("Saisissez la référence du produit à modifier : ");
      scanf("%d", &ref);
      vider_buffer();
      modify_product(ref);
      break;
    }
    case 3: {
      int ref;
      printf("Saisissez la référence du produit à supprimer : ");
      scanf("%d", &ref);
      vider_buffer();
      remove_product(ref);
      break;
    }
    case 4: {
      display_all_products();
      break;
    }
    case 5: {
      int ref;
      printf("Saisissez la référence du produit à afficher : ");
      scanf("%d", &ref);
      vider_buffer();
      display_product_by_ref(ref);
      break;
    }
    case 6: {
      char name[MAX_NAME];
      printf("Saisissez le nom du produit à afficher : ");
      scanf(" %[^\n]", name);
      vider_buffer();
      display_product_by_name(name);
      break;
    }
    case 7: {
      int ref;
      printf("Saisissez la référence du produit : ");
      scanf("%d", &ref);
      vider_buffer();
      increase_stock(ref);
      break;
    }
    case 8: {
      gestion_stock(products, numProducts, totalSpace);
      break;
    }
    case 9: {
      printf("=== A tres vite sur CY GESTION LIBRARY ===\n");
      break;
    }
    default:
      printf("Choix invalide. Veuillez réessayer.\n");
    }

    printf("\n");
  } while (choice != 9);
}