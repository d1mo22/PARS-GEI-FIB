;;; ---------------------------------------------------------
;;; ontologia.clp
;;; Translated by owl2clips
;;; Translated to CLIPS from ontology Ontologia_SBC.ttl
;;; :Date 06/12/2024 16:29:17

(defclass Epoca
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot epoca_tiene_obra
        (type INSTANCE)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
)

(defclass Estilo
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot estilo_tiene_obra
        (type INSTANCE)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
)

(defclass Obra
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (slot obra_tiene_epoca
        (type INSTANCE)
        (create-accessor read-write))
    (slot obra_tiene_estilo
        (type INSTANCE)
        (create-accessor read-write))
    (slot obra_tiene_pintor
        (type INSTANCE)
        (create-accessor read-write))
    (slot obra_tiene_tematica
        (type INSTANCE)
        (create-accessor read-write))
    (slot Complejidad
        (type SYMBOL)
        (create-accessor read-write))
    (slot Data_creacion
        (type SYMBOL)
        (create-accessor read-write))
    (slot Dimensiones_alto
        (type FLOAT)
        (create-accessor read-write))
    (slot Dimensiones_largo
        (type FLOAT)
        (create-accessor read-write))
    (slot Importancia
        (type SYMBOL)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
    (slot Sala
        (type INTEGER)
        (create-accessor read-write))
)

(defclass Pintor
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot pintor_tiene_obra
        (type INSTANCE)
        (create-accessor read-write))
    (slot Nacionalidad
        (type STRING)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
)

(defclass Preferencia
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot preferencia_de_epoca
        (type INSTANCE)
        (create-accessor read-write))
    (multislot preferencia_de_estilo
        (type INSTANCE)
        (create-accessor read-write))
    (multislot preferencia_de_pintor
        (type INSTANCE)
        (create-accessor read-write))
    (multislot preferencia_de_tematica
        (type INSTANCE)
        (create-accessor read-write))
)

(defclass Tematica
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot tematica_tiene_obra
        (type INSTANCE)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
)

(defclass Visita
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot vista_tiene_preferencia
        (type INSTANCE)
        (create-accessor read-write))
    (slot Conocimiento_visita
        (type SYMBOL)
        (create-accessor read-write))
    (slot Duracion_visita
        (type INTEGER)
        (create-accessor read-write))
    (slot Hay_peques_visita
        (type SYMBOL)
        (create-accessor read-write))
    (slot Ndias_visita
        (type INTEGER)
        (create-accessor read-write))
    (slot Npersonas_visita
        (type INTEGER)
        (create-accessor read-write))
)

(definstances instances
    ([Alegoria] of Tematica
         (tematica_tiene_obra [El_Esclavo_Moribundo] [El_Leon_de_Monzon])
         (Nombre "Alegoria")
    )

    ([Alejandro_de_Antioquia] of Pintor
         (pintor_tiene_obra [La_Venus_de_Milo])
         (Nacionalidad "Turca")
         (Nombre  "Alejandro de Antioquía")
    )

    ([Art_Nouveau] of Estilo
         (estilo_tiene_obra [El_Beso])
         (Nombre "Art Nouveau")
    )

    ([Asirio] of Estilo
         (estilo_tiene_obra [Los_Toros_Alados])
         (Nombre "Asirio")
    )

    ([Barroco] of Estilo
         (estilo_tiene_obra [El_Tahur] [La_Encajera] [La_joven_de_la_perla] [Las_Meninas] [Los_Caballos_de_Marly])
         (Nombre "Barroco")
    )

    ([Chica_frente_a_un_espejo] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Cubismo])
         (obra_tiene_pintor  [Pablo_Picasso])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  4)
         (Data_creacion  1932)
         (Dimensiones_alto  200)
         (Dimensiones_largo  300)
         (Importancia  4)
         (Nombre  "Chica frente a un espejo")
         (Sala  6)
    )

    ([Cisnes_reflejando_elefantes] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Surrealismo])
         (obra_tiene_pintor  [Salvador_Dali])
         (obra_tiene_tematica  [Reflejo])
         (Complejidad  5)
         (Data_creacion  1937)
         (Dimensiones_alto  200)
         (Dimensiones_largo  400)
         (Importancia  5)
         (Nombre  "Cisnes reflejando elefantes")
         (Sala  7)
    )

    ([Costumbrista] of Tematica
         (tematica_tiene_obra  [El_Bano_Turco] [El_Tahur] [La_Encajera])
         (Nombre  "Costumbrista")
    )

    ([Cubismo] of Estilo
         (estilo_tiene_obra  [Chica_frente_a_un_espejo] [Guernica] [Las_senoritas_de_Avignon])
         (Nombre  "Cubismo")
    )

    ([Desconocido] of Pintor
         (pintor_tiene_obra  [El_Escriba_Sentado] [El_Leon_de_Monzon] [Gabrielle_d_Estrees_y_Su_Hermana] [La_Momia] [La_Victoria_de_Samotracia] [Los_Toros_Alados])
         (Nacionalidad  "Desconocida")
         (Nombre  "Desconocido")
    )

    ([Edward_Hopper] of Pintor
         (pintor_tiene_obra  [Nighthawks])
         (Nacionalidad  "Estadounidense")
         (Nombre  "Edward Hopper")
    )

    ([Egipcio] of Estilo
         (estilo_tiene_obra  [El_Escriba_Sentado] [La_Momia])
         (Nombre  "Egipcio")
    )

    ([El_Bano_Turco] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [Neoclasicismo])
         (obra_tiene_pintor  [JeanAugusteDominique_Ingres])
         (obra_tiene_tematica  [Costumbrista])
         (Complejidad  4)
         (Data_creacion  1862)
         (Dimensiones_alto  110)
         (Dimensiones_largo  110)
         (Importancia  2)
         (Sala  4)
         (Nombre "El baño turco")
    )

    ([El_Beso] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Art_Nouveau])
         (obra_tiene_pintor  [Gustav_Klimt])
         (obra_tiene_tematica  [Alegoria])
         (Complejidad  4)
         (Data_creacion  1907)
         (Dimensiones_alto  180)
         (Dimensiones_largo  180)
         (Importancia  3)
         (Nombre  "El Beso")
         (Sala  4)
    )

    ;;; Esta obra es una estatua
    ([El_Esclavo_Moribundo] of Obra
         (obra_tiene_epoca  [Siglo_XVI])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [MiguelAngel_Buonarroti])
         (obra_tiene_tematica  [Alegoria])
         (Complejidad  4)
         (Data_creacion  1513)
         (Dimensiones_alto  229)
         (Importancia  2)
         (Nombre  "Esclavo moribundo")
         (Sala  2)
    )

    ([El_Escriba_Sentado] of Obra
         (obra_tiene_epoca  [Siglo_XXVI_aC])
         (obra_tiene_estilo  [Egipcio])
         (obra_tiene_pintor  [Desconocido])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  3)
         (Data_creacion  -2480)
         (Dimensiones_alto  54)
         (Nombre  "El escriba sentado")
         (Sala  1)
    )

    ([El_Greco] of Pintor
         (pintor_tiene_obra  [El_caballero_de_la_mano_en_el_pecho])
         (Nacionalidad  "Español")
         (Nombre  "El Greco")
    )

    ([El_Grito] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [Expresionismo])
         (obra_tiene_pintor  [Munch])
         (obra_tiene_tematica  [Expresionista])
         (Complejidad  4)
         (Data_creacion  1893)
         (Dimensiones_alto  91)
         (Dimensiones_largo  73.5)
         (Importancia  3)
         (Nombre  "El Grito")
         (Sala  4)
    )

    ;;; Esta obra es una estatua
    ([El_Leon_de_Monzon] of Obra
         (obra_tiene_epoca  [Siglo_XII])
         (obra_tiene_estilo  [Gotico])
         (obra_tiene_pintor  [Desconocido])
         (obra_tiene_tematica  [Alegoria])
         (Complejidad  2)
         (Data_creacion  1100)
         (Dimensiones_alto  31)
         (Importancia  1)
         (Nombre  "León de Monzón")
         (Sala  2)
    )

    ([El_Nacimiento_de_Venus] of Obra
         (obra_tiene_epoca  [Siglo_XV])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [Sandro_Botticelli])
         (obra_tiene_tematica  [Mitologico])
         (Complejidad  5)
         (Data_creacion  1485)
         (Dimensiones_alto  172.5)
         (Dimensiones_largo  278.5)
         (Importancia  3)
         (Nombre  "El nacimiento de Venus")
         (Sala  2)
    )

    ([El_Tahur] of Obra
         (obra_tiene_epoca  [Siglo_XVII])
         (obra_tiene_estilo  [Barroco])
         (obra_tiene_pintor  [Georges_deLaTour])
         (obra_tiene_tematica  [Costumbrista])
         (Complejidad  3)
         (Data_creacion  1635)
         (Dimensiones_alto  106)
         (Dimensiones_largo  146)
         (Importancia  1)
         (Nombre  "El tahúr")
         (Sala  3)
    )

    ([El_caballero_de_la_mano_en_el_pecho] of Obra
         (obra_tiene_epoca  [Siglo_XVI])
         (obra_tiene_estilo  [Mannerismo])
         (obra_tiene_pintor  [El_Greco])
         (obra_tiene_tematica  [Religioso])
         (Complejidad  4)
         (Data_creacion  1590)
         (Dimensiones_alto  120)
         (Dimensiones_largo  150)
         (Importancia  3)
         (Nombre  "El caballero de la mano en el pecho")
         (Sala  3)
    )

    ([El_jardin_de_las_delicias] of Obra
         (obra_tiene_epoca  [Siglo_XV])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [Hieronymus_Bosch])
         (obra_tiene_tematica  [Mitologico])
         (Complejidad  5)
         (Data_creacion  1490)
         (Dimensiones_alto  220)
         (Dimensiones_largo  389)
         (Importancia  3)
         (Nombre  "El jardín de las delicias")
         (Sala  5)
    )

    ([Eugene_Delacroix] of Pintor
         (pintor_tiene_obra  [La_Libertad_Guiando_al_Pueblo])
         (Nacionalidad  "Frances")
         (Nombre  "Eugène Delacroix")
    )

    ([Expresionismo] of Estilo
         (estilo_tiene_obra  [El_Grito] [Las_Aves])
         (Nombre  "Expresionismo")
    )

    ([Expresionista] of Tematica
         (tematica_tiene_obra  [El_Grito])
         (Nombre  "Expresionista")
    )

    ([Fantástico] of Tematica
         (tematica_tiene_obra  [Los_elefantes])
         (Nombre  "Fantastico")
    )

    ([Gabrielle_d_Estrees_y_Su_Hermana] of Obra
         (obra_tiene_epoca  [Siglo_XVI])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [Desconocido])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  3)
         (Data_creacion  1594)
         (Dimensiones_alto  96)
         (Dimensiones_largo  125)
         (Importancia  1)
         (Nombre  "Gabrielle d'Estrées y una de sus hermanas")
         (Sala  2)
    )

    ([Georges_Braque] of Pintor
         (pintor_tiene_obra  [Las_Aves])
         (Nacionalidad  "Frances")
         (Nombre  "Georges Braque")
    )

    ([Georges_deLaTour] of Pintor
         (pintor_tiene_obra  [El_Tahur])
         (Nacionalidad  "Frances")
         (Nombre  "Georges de La Tour")
    )

    ([Gotico] of Estilo
         (estilo_tiene_obra  [El_Leon_de_Monzon])
         (Nombre  "Gotico")
    )

    ([Griego_Helenistico] of Estilo
         (estilo_tiene_obra  [La_Venus_de_Milo] [La_Victoria_de_Samotracia] [Las_Bodas_de_Cana])
         (Nombre  "Griego Helenistico")
    )

    ([Guernica] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Cubismo])
         (obra_tiene_pintor  [Pablo_Picasso])
         (obra_tiene_tematica  [Historico])
         (Complejidad  5)
         (Data_creacion  1937)
         (Dimensiones_alto  349.3)
         (Dimensiones_largo  776.6)
         (Importancia  3)
         (Nombre  "Guernica")
         (Sala  5)
    )

    ([Guillaume_Coustou] of Pintor
         (pintor_tiene_obra  [Los_Caballos_de_Marly])
         (Nacionalidad  "Frances")
         (Nombre  "Guillaume Coustou")
    )

    ([Gustav_Klimt] of Pintor
         (pintor_tiene_obra  [El_Beso])
         (Nacionalidad  "Austríaco")
         (Nombre  "Gustav Klimt")
    )

    ([Hieronymus_Bosch] of Pintor
         (pintor_tiene_obra  [El_jardin_de_las_delicias])
         (Nacionalidad  "Holandés")
         (Nombre  "Hieronymus Bosch")
    )

    ([Historico] of Tematica
         (tematica_tiene_obra  [Guernica] [La_Libertad_Guiando_al_Pueblo] [La_Momia] [La_consagracion_de_Napoleon])
         (Nombre  "Historico")
    )

    ([JacquesLouis_David] of Pintor
         (pintor_tiene_obra  [La_consagracion_de_Napoleon])
         (Nacionalidad  "Frances")
         (Nombre  "Jacques-Louis David")
    )

    ([JeanAugusteDominique_Ingres] of Pintor
         (pintor_tiene_obra  [El_Bano_Turco])
         (Nacionalidad  "Frances")
         (Nombre  "Jean-Auguste-Dominique Ingres")
    )

    ([Johannes_Vermeer] of Pintor
         (pintor_tiene_obra  [La_Encajera] [La_joven_de_la_perla])
         (Nacionalidad "Holandés")
         (Nombre  "Johannes Vermeer")
    )

    ([La_Balsa_dela_Medusa] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [Romanticismo])
         (obra_tiene_pintor  [Theodore_Gericault])
         (obra_tiene_tematica  [Tragedia])
         (Complejidad  5)
         (Data_creacion  1819)
         (Dimensiones_alto  491)
         (Dimensiones_largo  716)
         (Importancia  3)
         (Nombre  "La balsa de la medusa")
         (Sala  4)
    )

    ([La_Encajera] of Obra
         (obra_tiene_epoca  [Siglo_XVII])
         (obra_tiene_estilo  [Barroco])
         (obra_tiene_pintor  [Georges_deLaTour])
         (obra_tiene_tematica  [Costumbrista])
         (Complejidad  3)
         (Data_creacion  1669)
         (Dimensiones_alto  24)
         (Dimensiones_largo  20)
         (Importancia  2)
         (Nombre  "La encajera")
         (Sala  3)
    )

    ([La_Gioconda] of Obra
         (obra_tiene_epoca  [Siglo_XV])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [Leonardo_DaVinci])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  4)
         (Data_creacion  1503)
         (Dimensiones_alto  77)
         (Dimensiones_largo  53)
         (Importancia  3)
         (Nombre  "La Gioconda")
         (Sala  2)
    )

    ([La_Libertad_Guiando_al_Pueblo] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [Romanticismo])
         (obra_tiene_pintor  [Eugene_Delacroix])
         (obra_tiene_tematica  [Historico])
         (Complejidad  5)
         (Data_creacion  1830)
         (Dimensiones_alto  260)
         (Dimensiones_largo  325)
         (Importancia  3)
         (Nombre  "La libertad guiando al pueblo")
         (Sala  4)
    )

    ;;; Esta obra es una estatua
    ([La_Momia] of Obra
         (obra_tiene_epoca  [Siglo_XXVI_aC])
         (obra_tiene_estilo  [Egipcio])
         (obra_tiene_pintor  [Desconocido])
         (obra_tiene_tematica  [Historico])
         (Complejidad  2 )
         (Dimensiones_alto 160)
         (Data_creacion -2500)
         (Importancia  2)
         (Sala  1)
         (Nombre "La momia")
    )

    ([La_Noche_Estrellada] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [PostImpresionismo])
         (obra_tiene_pintor  [VanGogh])
         (obra_tiene_tematica  [Paisaje])
         (Complejidad  4)
         (Data_creacion  1889)
         (Dimensiones_alto  73.7)
         (Dimensiones_largo  92.1)
         (Importancia  3)
         (Nombre  "La noche estrellada")
         (Sala  4)
    )

    ;;; Esta obra es una estatua
    ([La_Venus_de_Milo] of Obra
         (obra_tiene_epoca  [Siglo_II_aC])
         (obra_tiene_estilo  [Griego_Helenistico])
         (obra_tiene_pintor  [Alejandro_de_Antioquia])
         (obra_tiene_tematica  [Mitologico])
         (Complejidad  3)
         (Data_creacion  -120)
         (Dimensiones_alto  211)
         (Importancia  3)
         (Nombre  "La Venus de Milo")
         (Sala  1)
    )

    ;;; Esta obra es una estatua
    ([La_Victoria_de_Samotracia] of Obra
         (obra_tiene_epoca  [Siglo_II_aC])
         (obra_tiene_estilo  [Griego_Helenistico])
         (obra_tiene_pintor  [Desconocido])
         (obra_tiene_tematica  [Mitologico])
         (Complejidad  4)
         (Data_creacion  -190)
         (Dimensiones_alto  275)
         (Importancia  3)
         (Nombre  "Victoria alada de Samotracia")
         (Sala  1)
    )

    ([La_consagracion_de_Napoleon] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [Neoclasicismo])
         (obra_tiene_pintor  [JacquesLouis_David])
         (obra_tiene_tematica  [Historico])
         (Complejidad  4)
         (Data_creacion  1806)
         (Dimensiones_alto  667)
         (Dimensiones_largo  990)
         (Importancia  2)
         (Nombre  "La consagración de Napoleón")
         (Sala  4)
    )

    ([La_joven_de_la_perla] of Obra
         (obra_tiene_epoca  [Siglo_XVII])
         (obra_tiene_estilo  [Barroco])
         (obra_tiene_pintor  [Johannes_Vermeer])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  4)
         (Data_creacion  1665)
         (Dimensiones_alto  44.5)
         (Dimensiones_largo  39)
         (Importancia  3)
         (Nombre  "La joven de la perla")
         (Sala  4)
    )

    ([La_persistencia_de_la_memoria] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Surrealismo])
         (obra_tiene_pintor  [Salvador_Dali])
         (obra_tiene_tematica  [Surrealista])
         (Complejidad  5)
         (Data_creacion  1931)
         (Dimensiones_alto  24)
         (Dimensiones_largo  33)
         (Importancia  3)
         (Nombre  "La persistencia de la memoria")
         (Sala  5)
    )

    ([La_terraza_del_café_por_la_noche] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [PostImpresionismo])
         (obra_tiene_pintor  [VanGogh])
         (obra_tiene_tematica  [Urbano])
         (Complejidad  4)
         (Data_creacion  1888)
         (Dimensiones_alto  80)
         (Dimensiones_largo  65)
         (Importancia  4)
         (Nombre  "La terraza del café por la noche")
         (Sala  2)
    )

    ([La_ultima_cena] of Obra
         (obra_tiene_epoca  [Siglo_XV])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [Leonardo_DaVinci])
         (obra_tiene_tematica  [Religioso])
         (Complejidad  5)
         (Data_creacion  1495)
         (Dimensiones_alto  460)
         (Dimensiones_largo  880)
         (Importancia  3)
         (Nombre  "La última cena")
         (Sala  3)
    )

    ([Las_Aves] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Expresionismo])
         (obra_tiene_pintor  [Georges_Braque])
         (obra_tiene_tematica  [Naturaleza])
         (Complejidad  4)
         (Data_creacion  1953)
         (Dimensiones_alto  501)
         (Dimensiones_largo  347)
         (Importancia  1)
         (Nombre  "Las aves")
         (Sala  5)
    )

    ([Las_Bodas_de_Cana] of Obra
         (obra_tiene_epoca  [Siglo_XVI])
         (obra_tiene_estilo  [Griego_Helenistico])
         (obra_tiene_pintor  [Paolo_Veronese])
         (obra_tiene_tematica  [Religioso])
         (Complejidad  5)
         (Data_creacion  1563)
         (Dimensiones_alto  666)
         (Dimensiones_largo  990)
         (Importancia  2)
         (Nombre  "Las bodas de caná")
         (Sala  3)
    )

    ([Las_Meninas] of Obra
         (obra_tiene_epoca  [Siglo_XVII])
         (obra_tiene_estilo  [Barroco])
         (obra_tiene_pintor  [Velazquez])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  5)
         (Data_creacion  1656)
         (Dimensiones_alto  318)
         (Dimensiones_largo  276)
         (Importancia  3)
         (Nombre  "Las Meninas")
         (Sala  3)
    )

    ([Las_senoritas_de_Avignon] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Cubismo])
         (obra_tiene_pintor  [Pablo_Picasso])
         (obra_tiene_tematica  [Modernismo])
         (Complejidad  4)
         (Data_creacion  1907)
         (Dimensiones_alto  243.9)
         (Dimensiones_largo  233.7)
         (Importancia  3)
         (Nombre  "Las señoritas de Avignon")
         (Sala  5)
    )

    ([Leonardo_DaVinci] of Pintor
         (pintor_tiene_obra  [La_Gioconda] [La_ultima_cena])
         (Nacionalidad  "Italiano")
         (Nombre  "Leonardo Da Vinci")
    )

    ;;; Esta obra es una estatua
    ([Los_Caballos_de_Marly] of Obra
         (obra_tiene_epoca  [Siglo_XVIII])
         (obra_tiene_estilo  [Barroco])
         (obra_tiene_pintor  [Guillaume_Coustou])
         (obra_tiene_tematica  [Naturaleza])
         (Complejidad  3)
         (Data_creacion  1745)
         (Dimensiones_alto  340)
         (Importancia  1)
         (Nombre  "Caballos de Marly")
         (Sala  3)
    )

    ;;; Esta obra es una estatua
    ([Los_Toros_Alados] of Obra
         (obra_tiene_epoca  [Siglo_IX_aC])
         (obra_tiene_estilo  [Asirio])
         (obra_tiene_pintor  [Desconocido])
         (obra_tiene_tematica  [Mitologico])
         (Complejidad  3)
         (Data_creacion  -706)
         (Dimensiones_alto  300)
         (Importancia  1)
         (Nombre  "Lammasu")
         (Sala  1)
    )

    ([Los_elefantes] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Surrealismo])
         (obra_tiene_pintor  [Salvador_Dali])
         (obra_tiene_tematica  [Fantástico])
         (Complejidad  4)
         (Data_creacion  1948)
         (Dimensiones_alto  150)
         (Dimensiones_largo  300)
         (Importancia  4)
         (Nombre  "Los elefantes")
         (Sala  7)
    )

    ([Los_girasoles] of Obra
         (obra_tiene_epoca  [Siglo_XIX])
         (obra_tiene_estilo  [PostImpresionismo])
         (obra_tiene_pintor  [VanGogh])
         (obra_tiene_tematica  [Paisaje])
         (Complejidad  3)
         (Data_creacion  1888)
         (Dimensiones_alto  95)
         (Dimensiones_largo  73)
         (Importancia  4)
         (Nombre  "Los girasoles")
         (Sala  2)
    )

    ([Mannerismo] of Estilo
         (estilo_tiene_obra  [El_caballero_de_la_mano_en_el_pecho])
         (Nombre  "Mannerismo")
    )

    ([MiguelAngel_Buonarroti] of Pintor
         (pintor_tiene_obra  [El_Esclavo_Moribundo])
         (Nacionalidad  "Italiano")
         (Nombre  "Miguel Ángel Buonar")
    )

    ([Mitologico] of Tematica
         (tematica_tiene_obra  [El_Nacimiento_de_Venus] [El_jardin_de_las_delicias] [La_Venus_de_Milo] [La_Victoria_de_Samotracia] [Los_Toros_Alados])
         (Nombre  "Mitologico")
    )

    ([Modernismo] of Tematica
         (tematica_tiene_obra  [Las_senoritas_de_Avignon])
         (Nombre  "Modernismo")
    )

    ([Munch] of Pintor
         (pintor_tiene_obra  [El_Grito])
         (Nacionalidad  "Noruego")
         (Nombre  "Edvard Munch")
    )

    ([Naturaleza] of Tematica
         (tematica_tiene_obra  [Las_Aves] [Los_Caballos_de_Marly])
         (Nombre  "Naturaleza")
    )

    ([Neoclasicismo] of Estilo
         (estilo_tiene_obra  [El_Bano_Turco] [La_consagracion_de_Napoleon])
         (Nombre  "Neoclasicismo")
    )

    ([Nighthawks] of Obra
         (obra_tiene_epoca  [Siglo_XX])
         (obra_tiene_estilo  [Realismo_Moderno])
         (obra_tiene_pintor  [Edward_Hopper])
         (obra_tiene_tematica  [Soledad])
         (Complejidad  4)
         (Data_creacion  1942)
         (Dimensiones_alto  80)
         (Dimensiones_largo  155)
         (Importancia  3)
         (Nombre  "Nighthawks")
         (Sala  5)
    )

    ([Pablo_Picasso] of Pintor
         (pintor_tiene_obra  [Chica_frente_a_un_espejo] [Guernica] [Las_senoritas_de_Avignon])
         (Nacionalidad  "Español")
         (Nombre  "Pablo Picasso")
    )

    ([Paisaje] of Tematica
         (tematica_tiene_obra  [La_Noche_Estrellada] [Los_girasoles])
         (Nombre  "Paisaje")
    )

    ([Paolo_Veronese] of Pintor
         (pintor_tiene_obra  [Las_Bodas_de_Cana])
         (Nacionalidad  "Italiano")
         (Nombre  "Paolo Veronese")
    )

    ([PostImpresionismo] of Estilo
         (estilo_tiene_obra  [La_Noche_Estrellada] [La_terraza_del_café_por_la_noche] [Los_girasoles])
         (Nombre  "PostImpresionismo")
    )

    ([Realismo_Moderno] of Estilo
         (estilo_tiene_obra  [Nighthawks])
         (Nombre  "Realismo morderno")
    )

    ([Reflejo] of Tematica
         (tematica_tiene_obra  [Cisnes_reflejando_elefantes])
         (Nombre  "Reflejo")
    )

    ([Religioso] of Tematica
         (tematica_tiene_obra  [El_caballero_de_la_mano_en_el_pecho] [La_ultima_cena] [Las_Bodas_de_Cana])
         (Nombre  "Religioso")
    )

    ([Renacimiento] of Estilo
         (estilo_tiene_obra  [El_Esclavo_Moribundo] [El_Nacimiento_de_Venus] [El_jardin_de_las_delicias] [Gabrielle_d_Estrees_y_Su_Hermana] [La_Gioconda] [La_ultima_cena] [Retrato_de_una_Joven])
         (Nombre  "Renacimiento")
    )

    ([Retrato] of Tematica
         (tematica_tiene_obra  [Chica_frente_a_un_espejo] [El_Escriba_Sentado] [Gabrielle_d_Estrees_y_Su_Hermana] [La_Gioconda] [La_joven_de_la_perla] [Las_Meninas] [Retrato_de_una_Joven])
         (Nombre  "Retrato")
    )

    ([Retrato_de_una_Joven] of Obra
         (obra_tiene_epoca  [Siglo_XV])
         (obra_tiene_estilo  [Renacimiento])
         (obra_tiene_pintor  [Sandro_Botticelli])
         (obra_tiene_tematica  [Retrato])
         (Complejidad  3)
         (Data_creacion  1480)
         (Dimensiones_alto  82)
         (Dimensiones_largo  54)
         (Importancia  1)
         (Nombre  "Retrato de una joven")
         (Sala  2)
    )

    ([Romanticismo] of Estilo
         (estilo_tiene_obra  [La_Balsa_dela_Medusa] [La_Libertad_Guiando_al_Pueblo])
         (Nombre  "Romanticismo")
    )

    ([Salvador_Dali] of Pintor
         (pintor_tiene_obra  [Cisnes_reflejando_elefantes] [La_persistencia_de_la_memoria] [Los_elefantes])
         (Nacionalidad  "Español")
         (Nombre  "Salvador Dalí")
    )

    ([Sandro_Botticelli] of Pintor
         (pintor_tiene_obra  [El_Nacimiento_de_Venus] [Retrato_de_una_Joven])
         (Nacionalidad  "Italiano")
         (Nombre  "Sandro Botticelli")
    )

    ([Siglo_II_aC] of Epoca
         (epoca_tiene_obra  [La_Venus_de_Milo] [La_Victoria_de_Samotracia])
         (Nombre  "Siglo II a.C")
    )

    ([Siglo_IX_aC] of Epoca
         (epoca_tiene_obra  [Los_Toros_Alados])
         (Nombre  "Siglo IX a.C")
    )

    ([Siglo_XII] of Epoca
         (epoca_tiene_obra  [El_Leon_de_Monzon])
         (Nombre  "Siglo XII")
    )

    ([Siglo_XIX] of Epoca
         (epoca_tiene_obra  [El_Bano_Turco] [La_Balsa_dela_Medusa] [La_Libertad_Guiando_al_Pueblo] [La_Noche_Estrellada] [La_consagracion_de_Napoleon] [La_terraza_del_café_por_la_noche] [Los_girasoles])
         (Nombre  "Siglo XIX")
    )

    ([Siglo_XV] of Epoca
         (epoca_tiene_obra  [El_Nacimiento_de_Venus] [El_jardin_de_las_delicias] [La_Gioconda] [La_ultima_cena] [Retrato_de_una_Joven])
         (Nombre  "Siglo XV")
    )

    ([Siglo_XVI] of Epoca
         (epoca_tiene_obra  [El_Esclavo_Moribundo] [El_caballero_de_la_mano_en_el_pecho] [Gabrielle_d_Estrees_y_Su_Hermana] [Las_Bodas_de_Cana])
         (Nombre  "Siglo XVI")
    )

    ([Siglo_XVII] of Epoca
         (epoca_tiene_obra  [El_Tahur] [La_Encajera] [La_joven_de_la_perla] [Las_Meninas])
         (Nombre  "Siglo XVII")
    )

    ([Siglo_XVIII] of Epoca
         (epoca_tiene_obra  [Los_Caballos_de_Marly])
         (Nombre  "Siglo XVIII")
    )

    ([Siglo_XX] of Epoca
         (epoca_tiene_obra  [Chica_frente_a_un_espejo] [Cisnes_reflejando_elefantes] [El_Beso] [Guernica] [La_persistencia_de_la_memoria] [Las_Aves] [Las_senoritas_de_Avignon] [Los_elefantes] [Nighthawks])
         (Nombre  "Siglo XX")
    )

    ([Siglo_XXVI_aC] of Epoca
         (epoca_tiene_obra  [El_Escriba_Sentado] [La_Momia])
         (Nombre  "Siglo XXVI a.C")
    )

    ([Soledad] of Tematica
         (tematica_tiene_obra  [Nighthawks])
         (Nombre  "Soledad")
    )

    ([Surrealismo] of Estilo
         (estilo_tiene_obra  [Cisnes_reflejando_elefantes] [La_persistencia_de_la_memoria] [Los_elefantes])
         (Nombre  "Surrealismo")
    )

    ([Surrealista] of Tematica
         (tematica_tiene_obra  [La_persistencia_de_la_memoria])
         (Nombre  "Surrealista")
    )

    ([Theodore_Gericault] of Pintor
         (pintor_tiene_obra  [La_Balsa_dela_Medusa])
         (Nacionalidad  "Frances")
         (Nombre  "Theodore Géricault")
    )

    ([Tragedia] of Tematica
         (tematica_tiene_obra  [La_Balsa_dela_Medusa])
         (Nombre  "Tragedia")
    )

    ([Urbano] of Tematica
         (tematica_tiene_obra  [La_terraza_del_café_por_la_noche] [Nighthawks])
         (Nombre  "Urbano")
    )

    ([VanGogh] of Pintor
         (pintor_tiene_obra  [La_Noche_Estrellada] [La_terraza_del_café_por_la_noche] [Los_girasoles])
         (Nacionalidad  "Holandes")
         (Nombre  "Vincent Van Gogh")
    )

    ([Velazquez] of Pintor
         (pintor_tiene_obra  [Las_Meninas])
         (Nacionalidad  "Español")
         (Nombre  "Diego Velázquez")
    )

)
