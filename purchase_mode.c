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

void purchase_mode() {
    int choix;

    do {
        printf("==== BIENVENUE CY LIBRARY ====\n");
        printf("==== MODE ACHATS ====\n");
        printf("1. Creer un compte\n");
        printf("2. Modifier un compte\n");
        printf("3. Supprimer un compte\n");
        printf("4. Afficher un compte\n");
        printf("5. Ajouter un achat\n");
        printf("6. Supprimer un achat\n");
        printf("7. Rechercher un achat\n");
        printf("8. Les 3 derniers achats d'un client\n");
        printf("9. Historique d'achats\n");
        printf("10. Afficher le montant total des achats d'un client\n");
        printf("11. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1:
                add_client(); // Appel à une fonction pour créer un compte client
                break;
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
                Client client;
                Achat achat;

                printf("Nom du client : ");
                fgets(client.client_name, sizeof(client.client_name), stdin);
                client.client_name[strcspn(client.client_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne
                printf("Prénom du client : ");
                fgets(client.client_firstname, sizeof(client.client_firstname), stdin);
                client.client_firstname[strcspn(client.client_firstname, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne

                printf("Nom du produit : ");
                fgets(achat.product_name, sizeof(achat.product_name), stdin);
                achat.product_name[strcspn(achat.product_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne
                printf("Quantité : ");
                scanf("%d", &achat.quantity);
                vider_buffer();
                printf("Prix unitaire : ");
                scanf("%f", &achat.unit_price);
                vider_buffer();

                add_achat(&client, achat); // Appel à une fonction pour ajouter un achat lié à un client
                break;
            }
            case 6: {
                char client_name[MAX_NAME];
                char product_name[MAX_NAME];

                printf("Nom du client : ");
                fgets(client_name, sizeof(client_name), stdin);
                client_name[strcspn(client_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne
                printf("Nom du produit : ");
                fgets(product_name, sizeof(product_name), stdin);
                product_name[strcspn(product_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne

                // Supprimer l'extension ".txt" du nom du client s'il est présent
                char* extension = ".txt";
                int extension_length = strlen(extension);
                int client_name_length = strlen(client_name);
                if (client_name_length > extension_length && strcmp(&client_name[client_name_length - extension_length], extension) == 0) {
                    client_name[client_name_length - extension_length] = '\0';
                }

                delete_achat(client_name, product_name); // Appel à une fonction pour supprimer un achat
                break;
            }
            case 7: {
                char client_name[MAX_NAME];
                int ref;

                printf("Nom du client : ");
                fgets(client_name, sizeof(client_name), stdin);
                client_name[strcspn(client_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne
                printf("Référence du produit : ");
                scanf("%d", &ref);
                vider_buffer();

                Client client = find_client(client_name, ""); // Appel à une fonction pour trouver un client
                Achat achat = find_achat(client, ref); // Appel à une fonction pour trouver un achat
                if (achat.quantity > 0) {
                    printf("Achat trouvé :\n");
                    printf("Nom du produit : %s\n", achat.product_name);
                    printf("Quantité : %d\n", achat.quantity);
                    printf("Prix unitaire : %.2f\n", achat.unit_price);
                } else {
                    printf("Aucun achat correspondant n'a été trouvé.\n");
                }
                break;
            }
            case 8: {
                char client_name[MAX_NAME];

                printf("Nom du client : ");
                fgets(client_name, sizeof(client_name), stdin);
                client_name[strcspn(client_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne

                display_three_last_achats(client_name); // Appel à une fonction pour afficher les 3 derniers achats d'un client
                break;
            }
            case 9: {
                char client_name[MAX_NAME];

                printf("Nom du client : ");
                fgets(client_name, sizeof(client_name), stdin);
                client_name[strcspn(client_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne

                display_achats(client_name); // Appel à une fonction pour afficher tous les achats d'un client
                break;
            }
            case 10: {
                char client_name[MAX_NAME];

                printf("Nom du fichier : ");
                fgets(client_name, sizeof(client_name), stdin);
                client_name[strcspn(client_name, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne

                float total_amount = calculate_total_amount_from_file(client_name); // Appel à une fonction pour calculer le montant total des achats d'un client
                printf("Montant total des achats pour le client : %.2f\n", total_amount);
                break;
            }
            case 11:
                printf("Au revoir ! A Bientot !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        printf("\n");
    } while (choix != 11);
}
