#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_NAME 100
#define MAX_HISTO 500
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME_LENGTH 50

void purchase_mode() {
    int choix;

    do {
        printf("====== BIENVENUE CY LIBRARY ======\n");
        printf("====== MODE ACHATS ======\n");
        printf("1. Connexion ou Créer un compte\n");
        printf("2. Modifier un compte\n");
        printf("3. Supprimer un compte\n");
        printf("4. Afficher un compte\n");
        printf("5. Effectuer un achat\n");
        printf("6. Les 3 derniers achats d'un client\n");
        printf("7. Historique d'achats\n");
        printf("8. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
           case 1: {
             int client_id;
             printf("ID du client : ");
             scanf("%d", &client_id);
             vider_buffer();
             
             if (client_exists(client_id)) {
               char reponse[10];
               printf("Le client avec l'ID %d a déjà un compte. Souhaitez-vous créer un nouveau compte ? (oui/non) ", client_id);
               fgets(reponse, sizeof(reponse), stdin);
               if (strcmp(reponse, "oui\n") == 0) {
                 add_client(); // Appel à une fonction pour créer un compte client
               } 
               else {
                 printf("Opération annulée. Retour au menu principal.\n");
               }
             } 
             else {
               add_client(); // Appel à une fonction pour créer un compte client
             }
             break;
           }
            case 2:
                modify_client(); // Appel à une fonction pour modifier un compte client
                break;
            case 3:
                delete_client(); // Appel à une fonction pour supprimer un compte client
                break;
            case 4:
                display_client(); // Appel à une fonction pour afficher un compte client
                break;
            case 5: {
              int client_id;
              Achat achat;
              
              // Demande de l'ID du client
              printf("ID du client : ");
              scanf("%d", &client_id);
              vider_buffer();
              
              // Vérifie si le client existe
              if (!client_exists(client_id)) {
                printf("Le client avec l'ID %d n'existe pas.\n", client_id);
                break;  // Si le client n'existe pas, termine la fonction
              }
              
              // Demande de la référence du produit
              printf("Référence du produit : ");
              scanf("%d", &achat.product_ref);
              vider_buffer();
              
              // Vérifie si le produit existe
              if (!product_exists(achat.product_ref)) {

                printf("Le produit avec la référence %d n'existe pas.\n", achat.product_ref);
                break;  // Si le produit n'existe pas, termine la fonction
              }
              // Demande de la quantité à acheter
              printf("Quantité : ");
              scanf("%d", &achat.quantity);
              vider_buffer();
              
              // Crée un objet Client avec l'ID donné
              Client client;
              client.client_id = client_id;
              
              // Ajoute l'achat au client
              add_achat(&client, achat);
              break;
            }
            case 6: {
              int client_id;
              printf("ID du client : ");
              scanf("%d", &client_id);
              vider_buffer(); // Pour consommer le caractère de nouvelle ligne restant
              display_three_last_achats(client_id); // Appel à une fonction pour afficher les 3 derniers achats d'un client en fonction de son ID
              break;
            }
            case 7: {
              int client_id;
              printf("ID du client : ");
              scanf("%d", &client_id);
              vider_buffer();  // Capturer le caractère de nouvelle ligne restant
              display_achats(client_id); // Appel à la fonction pour afficher tous les achats d'un client à partir de son ID
              break;
            }
            case 8:
                printf("====== A Bientôt à CY LIBRARY ====== !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        printf("\n");
    } while (choix != 8);
}
