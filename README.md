# BE_Cpp_Zac_Sophie

Notre application permet de détecter des flashs lumineux pouvant provoquer des crises d'épilepsie ainsi que de détecter des convulsions. Dans le contexte du Covid-19, nous avons réalisé ce projet sous simulateur Arduino, ce qui nous a obligé à simuler tous les capteurs et actionneurs. Les valeurs qu'ils nous retournent ne sont donc pas de "vraies" valeurs et nous n'actionnons pas de vrais actionneurs. Notre application fonctionne soit en mode détection de lumière soit en mode détection de convulsion, il faudra donc réaliser les étapes suivantes pour changer de mode :
Dans le fichier board.cpp, il faut que les lignes du Bouton Poussoir et du Bipeur soit toujours décommentés.
- Si l'on veut utiliser la lumière, on laisse aussi les lignes raccordant le luxmètre et la LED intelligente (dont l'argument fixe la période de clignottment, en ms). Ensuite, dans le fichier sketch_ino, on commente la ligne "mon_application->do_one_step_convulsions(1000);" et on garde "mon_application->do_one_step_lumiere(10);" .
- Si l'on veut utiliser le détcteur de convulsions, on commente dans le fichier board.cpp les lignes qui raccordent le luxmètre et la LED intelligente et on décommente tout le reste. Dans le fichier sketch_ino, on laisse la ligne "mon_application->do_one_step_convulsions(1000);" et on commente "mon_application->do_one_step_lumiere(10);".

Pour simuler une lumière qui peut provoquer une crise d'épilepsie, il faut fixer la période de la LED intelligente (dans le fichier board.cpp) entre 25 et 33.
Pour simuler des secousses qui provoquent un déclenchement de la détection de convulsions, il faut choisir une amplitude du Shaker supérieure à 3. A 1, les secousses sont suffisamment faibles pour être détectées parfois mais elles ne déclencheront pas l'avertissement car trop peu importantes successivement.
