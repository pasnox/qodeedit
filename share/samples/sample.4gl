FUNCTION ma_fonction3(ma_date)
  DEFINE ma_date DATE
  DEFINE mon_tableau ARRAY[20] OF RECORD
     date_naiss DATE,
     nom CHAR(20),
     prenom CHAR(20),
     ville CHAR(20)
  END RECORD
  DEFINE idx smallint
   DECLARE c_date CURSOR FOR
   SELECT date_naissance, nom, prenom, ville
   FROM ma_table
   LET idx=1
   FOREACH c_date INTO mon_tableau[idx].* # valoriser l'élément du tableau avec la rangée courante
      LET idx = idx + 1   # incrémenter l'indice du tableau
   END FOREACH
   LET idx=idx-1 # le nombre exact d'éléments ( -1 car le foreach termine avec la valeur correcte + 1 )
   IF idx > 0 THEN
      open window ma_window at 3,55
      with form "ma_forme" attribute (border) # créer une window en ligne 3, colonne 55, à partir de la forme ma_forme.per/frm
      CALL set_count(idx)
      DISPLAY ARRAY mon_tableau TO sa_tableau # afficher le contenu du tableau dans le screen record défini dans ma_forme.per
   ELSE
      ERROR "Pas de données à afficher"
   END IF
END FUNCTION