# Cy-Shop  
Projet Préing1 MEF1 Mariam Sawsene Marwa

Présentation Générale: 
<img width="329" alt="main" src="https://github.com/Marwa-zag/Cy-Shop-/assets/131346380/e0c39dfe-047a-4bb9-8929-ba72d1549ab5">


Cy-Shop est une librairie en ligne qui permet de se connecter à un compte et de pouvoir acheter un ou plusieurs articles. Le programme a été codé avec solidité et rigueur dans le but de permettre aux employés de mieux gérer l'état du stock de leur magasin, et aussi de permettre aux clients d'apprécier leur expérience lors des achats.
Il existe deux modes, le mode gestion et le mode achat. Le mode gestion est principalement consacré pour les employés de la librairie et le mode achat pour les clients. 

# Mode Gestion - Gestion des stocks
<img width="319" alt="mode gestion" src="https://github.com/Marwa-zag/Cy-Shop-/assets/131346380/6795e2c0-8a0f-4a5c-854c-0413d122a88c">


Le mode gestion de ce programme permet de gérer les stocks du magasin. Il offre des fonctionnalités pour afficher les produits nécessitant un restockage urgent, connaître le stock d'un produit spécifique, augmenter le stock d'un produit et vérifier la capacité de stockage du magasin.
 
Fonctionnalités

Affichage des produits nécessitant un restockage urgent :
Lorsque le mode gestion est sélectionné, en appelant la fonction afficher stock_bas, le programme affiche les produits dont les stocks sont à 0 ainsi que les 5 produits dont les stocks sont les plus bas. Cela permet à l'utilisateur de connaître les besoins urgents en restockage.

Affichage de la place restante en magasin :
Le programme affiche également la place restante en magasin, en tenant compte des différentes tailles des produits (petit, moyen, grand) et de leur capacité de stockage. Cela permet de savoir combien d'emplacements sont disponibles pour de nouveaux produits.

Consultation du stock d'un produit :
L'utilisateur peut rechercher le stock d'un produit en spécifiant soit son nom, soit sa référence. Le programme affiche ensuite la quantité en stock du produit recherché.

Augmentation du stock d'un produit :
L'utilisateur a la possibilité d'augmenter le stock d'un produit spécifique. Le programme demande ensuite la quantité à ajouter au stock existant et effectue la mise à jour correspondante.

Vérification de la capacité de stockage :
Étant donné que le magasin a une capacité de stockage limitée, le programme vérifie si une demande d'ajout de produits dépasserait cette capacité. Si la demande dépasse la capacité disponible, le programme la refuse.

Concernant les fichiers, les informations des produits sont stockées dans un fichier texte spécifique. Chaque ligne du fichier représente un produit avec ses informations séparées. Le nom du fichier se nomme produits.txt.

Le programme peut également modifier un produit, supprimer un produit...

Instructions d'utilisation

Lancer le programme et sélectionner le mode gestion.
Utiliser les options du menu pour consulter le stock d'un produit, augmenter le stock d'un produit ou vérifier la capacité de stockage...
Suivre les instructions du programme pour effectuer les actions souhaitées.
    
    
    
    
    
  # Mode Achat 
   # Mode Achat

<img width="362" alt="mode achats" src="https://github.com/Marwa-zag/Cy-Shop-/assets/131346380/dcecb932-cc75-4b67-8259-98628b57590c">

Dans ce mode, les clients peuvent choisir s'ils possèdent déjà un compte ou s'ils sont de nouveaux clients.
Si le client est nouveau, son profil client sera créé et ajouté à la base de données des clients.
Les clients existants pourront voir les trois derniers achats, ils pourront également acheter des produits.
Le prix total des achats sera affiché à la fin de la transaction. si un client ne souhaite pas créer un compte il pourra quand même s'il le souhaite effectuer des achats. 
Si un produit souhaité n'est plus disponible, les clients mécontents ont la possibilité de se désinscrire de la liste des clients et d'explorer d'autres options, autrement dit aller vers d'autres librairies. Cela entraînera la suppression des fichiers associés au client.
Concernant les fichiers, les informations des clients sont stockées dans des fichiers texte individuels, chaque fichier porte le nom du client.
    
# Difficultés rencontrés 

Nous avons eu du mal à créer une fonction qui permet de trouver un produit et qui l'affiche dans le panier du client, mais aussi pour afficher le montant total des produits. 
Nous avons également eu du mal pour regarder si le client est déjà existant dans la base de données.

 
    
    
    
    
    
    
    
    
