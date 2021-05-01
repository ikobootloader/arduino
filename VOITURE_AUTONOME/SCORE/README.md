 * <h1>VOITURE AUTONOME</h1> - mod SCORE - Version 1
 * 
 * ::PRINCIPE::
 * Il y a 4 réactions différentes possibles face à un obstacle :
 * AVANCER || RECULER || GAUCHE || DROITE
 * Par défaut, pour chaque angle (5 amplitudes) balayé par le servomoteur 
 * c'est l'action AVANCER qui possède le meilleur score (1).
 * Lorsque la voiture s'approche d'un obstacle, elle teste l'action
 * qui possède le meilleur score selon l'angle en cours de balayage
 * Si l'action permet au véhicule d'éviter l'obstacle, elle conserve son score à 1
 * Si l'action ne permet pas au véhicule d'éviter l'obstacle,
 * d'autres actions sont testées. C'est l'action qui permet au véhicule
 * d'éviter l'obtacle qui obtient un score à un 1. Toutes les autres actions affichent un score de 0
