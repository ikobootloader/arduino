  <H1>NOMENCLATURE </H1>
  
  <H2>//////// FONCTIONS SUR VARIABLES ////////</H2>
  
  <H3>//Concaténation de 2 valeurs</H3>
  /*<br>
  int c1= 5;<br>
  int c2 = 99; <br>
  int c3 = f.concatenation(c1,c2); //Retourne 599<br>
  */

  <H2>//////// FONCTIONS SUR LE TEMPS ////////</H2>

  <H3>//Créer une fréquence</H3>
  /*
  // f.frequence(limite de temps à insérer en millisecondes)<br>
  f.frequence(1000); //la fonction renvoie true toute les secondes<br>
  */

  /***/

  <H3>//Créer un intervalle de temps à partir de la fonction f.frequence()</H3>
  /*
  bool val  = f.frequence(1000);<br>
  f.intervalle(val,10);<br>
  f.resetIntervalle() permet de réinitialiser à 0 la méthode f.compteurIntervalle <br>
  Le résultat est tjs retourné dans la méthode f.compteurIntervalle <br>
  i(f.compteurIntervalle) <br>
  */

  <H2>//////// FONCTIONS SUR TABLEAUX ////////</H2>

  <H3>//Retounrner la taille d'un tableau => SIZE_ARR(tableau);</H3>
  
  //Retourner la valeur la plus courante
  /*
  f.plusFrequent(nom du tableau, taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};<br>
  f.plusFrequent(tab,SIZE_ARR(tab)) <=> f.plusFrequent(tab,10);<br>
  */

  /***/

  <H3>//Trouver la valeur la plus petite</H3>
  /*
  //f.mini(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  int val = f.mini(tab,10); //Retourne 0
  i(val)
  */

  /***/

  <H3>//Trouver la valeur la plus grande</H3>
  /*
  //f.maxi(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7}; //Retourne 9
  int val = f.maxi(tab,10);
  i(val)  
  */

  /***/

  <H3>//Trier un tableau dans l'ordre croissant</H3>
  /*
  //f.triAsc(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.triAsc(tab,10);
  for(int i = 0; i <= 9;i++){
    i(tab[i])    
  }  
  */

  /***/

  <H3>//Trier un tableau dans l'ordre décroissant</H3>
  /*
  //f.triDesc(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.triDesc(tab,10);
  for(int i = 0; i <= 9;i++){
    i(tab[i])    
  }  
  */  

  /***/

  <H3>//Inverser un tableau</H3>
  /*
  //f.inverser(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.inverser(tab,10);
  for(int i = 0; i <= 9;i++){
    i(tab[i])    
  }  
  */ 
