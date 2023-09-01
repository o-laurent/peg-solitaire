#include "rules.h"
#include <stdio.h>

void printRules() {
  char line[1024];
  printf("\033[1;4m"); // Bold Underlined
  printf("Règles du jeu de base :");
  printf("\033[0m");
  printf("\n");

  printf("Le solitaire est, comme son nom l’indique, un jeu où l’on n’a aucun "
         "adversaire.\n"
         "Le but est de déplacer des billes sur un plateau, de les ôter petit "
         "à petit selon une règle précise "
         "jusqu’à ce qu’il ne reste qu’une seule bille au centre.\nLe joueur "
         "va prendre une bille et sauter par "
         "dessus la seconde se trouvant à coté pour aller rejoindre le trou "
         "vide.\nLa bille qui aura été sautée est alors sortie du jeu.\n"
         "Il faut savoir qu’à chaque coup, le joueur ne peut prendre qu’une "
         "seule bille à la fois et que cette dernière est prise par une autre "
         "bille venant verticalement ou horizontalement à elle.\n\n");

  printf("\033[37;2m");
  printf("Tapez sur une touche pour lire la suite...");
  printf("\033[0m");
  fgets(line, 1024, stdin);
  printf("\n");

  printf("\033[1;4m"); // Bold Underlined
  printf("Règles spécifiques à cette émulation du solitaire :");
  printf("\033[0m");
  printf("\n");
  printf("Tout d'abord, souvenez-vous que vous pouvez arrêter la partie à "
         "n'importe quel moment en tapant '-1'."
         " Vous pourrez alors sauvegarder la partie et la reprendre ou vous en "
         "étiez quand vous voulez.\n"
         "Les billes sont représentées par des \033[1mo\033[0m et les trous "
         "par des \033[37;2mx\033[0m.\n"
         "À chaque étape, le jeu vous demandera de fournir les coordonnées de "
         "la bille que vous voulez déplacer.\n"
         "Le déplacement de celle-ci est automatique si il n'y a qu'un couple "
         "(direction, sens) possible.\n"
         "Si il y en a plusieurs, vous devrez alors fournir le couple "
         "(direction, sens) souhaité sous la forme (n, s, e, o) :\n"
         "nord / sud / est / ouest"
         "\n\n");

  printf("\033[37;2m");
  printf("Tapez sur une touche pour lire la suite...");
  printf("\033[0m");
  fgets(line, 1024, stdin);
  printf("\n");

  printf("\033[1;4m"); // Bold Underlined
  printf("Quelques détails supplémentaires :");
  printf("\033[0m");
  printf("\n");

  printf("Vous pouvez utiliser la configuration, c'est-à-dire le plateau "
         "fourni, mais aussi en proposer un autre.\n"
         "Pour cela, il vous suffit de modifier data/model.txt en fournissant "
         "le plateau sous la forme déjà existante.\n"
         "Notez que de nombreux modèles sont d'ors et déjà proposés. Il vous "
         "suffit de les renommer en model.txt pour les utiliser."
         "\n\n");
}