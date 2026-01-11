;; 1. Definición de clases en CLIPS
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
        (type INTEGER)
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
         (obra_tiene_pintor  [Johannes_Vermeer])
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

;;2. Exportación del MAIN y definicion módulos
(defmodule MAIN (export ?ALL) )

(defmodule getInput (import MAIN ?ALL) (export ?ALL) )

(defmodule abstraccion (import MAIN ?ALL) (import getInput ?ALL) (export ?ALL) )

(defmodule asociacionHeuristica (import MAIN ?ALL) (import abstraccion ?ALL) (export ?ALL) )

(defmodule showResultado (import MAIN ?ALL) (import asociacionHeuristica ?ALL) (export ?ALL) )

(defrule MAIN::reglaInicial
	(declare (salience 10))
	=>
	(printout t crlf)
	(printout t "--------------------------------------------------------------" crlf)
	(printout t "|                     Práctica SBC Museo                      |" crlf)
	(printout t "--------------------------------------------------------------" crlf)
	(printout t crlf)
	(focus getInput) 
)

;; 3. Templates
(deftemplate MAIN::datosVisita
    (slot Npersonas_visita (type INTEGER) (default 0))
    (slot Conocimiento_visita (type INTEGER) (default 0))
    (slot Ndias_visita (type INTEGER) (default 0))
    (slot Duracion_visita (type INTEGER) (default 0))
    (slot Hay_peques_visita (type SYMBOL) (default FALSE))
    (multislot Tematica)
    (multislot Epoca)
    (multislot Estilo)
    (multislot Pintor)
)

(deftemplate MAIN::Obra_Preferente
    (slot Obra) 
    (slot Prioridad) 
    (slot Sala) 
    (slot Duracion) 
)

(deftemplate MAIN::Ruta
    (multislot Obras)    ; Multislot para almacenar la lista de obras
)

(deftemplate MAIN::Ruta_Diaria
    (slot Dia)
    (multislot Obras)
)

(deftemplate showResultado::contador
    (slot count (type INTEGER))
)

;; 5. Funciones
(deffunction getInput::pregunta_numero (?pregunta)
    (printout t ?pregunta)
    (bind ?respuesta (read))
    ?respuesta
)

(deffunction getInput::pregunta_numero_con_rango (?pregunta ?min ?max)
    (format t "%s " ?pregunta)
    (bind ?respuesta (read))
    
    ;; Validar que la respuesta sea un número y esté dentro del rango
    (while (or (not (integerp ?respuesta))
               (< ?respuesta ?min)
               (> ?respuesta ?max))
        (format t "Por favor, introduzca un número entre %d y %d: " ?min ?max)
        (bind ?respuesta (read))
    )
    
    ;; Devolver la respuesta válida
    (return ?respuesta)
)

(deffunction getInput::pregunta_boolean (?pregunta)
    (format t "%s[S/N] " ?pregunta)
    (bind ?respuesta (read))

    (while (not (or (eq ?respuesta S) (eq ?respuesta N)))
        (format t "Por favor, responda con S o N: ")
        (bind ?respuesta (read))
    )

    (if (eq ?respuesta S) 
        then (return TRUE)
        else (return FALSE)    ; Asegurar retorno explícito de FALSE
    ) 
)

(deffunction getInput::pregunta_opcion_unica (?pregunta $?opciones)
   (bind ?indice 1)
   (bind ?linea (format nil "%s" ?pregunta))
   (printout t ?linea crlf)

   (progn$ (?valor $?opciones)
      (bind ?linea (format nil "  %d. %s" ?indice ?valor))
      (printout t ?linea crlf)
      (bind ?indice (+ ?indice 1))
   )

   (format t "%s" "Indica tu respuesta (Escoge el indice correspondiente): ")
   (bind ?resp (read))
   (return ?resp)
)

(deffunction getInput::pregunta_opcion_multiple (?pregunta $?opciones)
   (printout t ?pregunta crlf)
   (loop-for-count (?i 1 (length$ ?opciones))
      (format t "  %d. %s%n" ?i (nth$ ?i ?opciones))
   )
   
   (format t "%nIndica los números separados por espacio: ")
   (readline)
   (bind ?entrada (readline))
   
   (bind ?indices (create$))
   (foreach ?token (explode$ ?entrada)  
      (if (numberp ?token) then
         (bind ?num (integer ?token))
         (if (and (>= ?num 1) 
                  (<= ?num (length$ ?opciones))) 
         then
            (bind ?indices (create$ ?indices ?num))
         )
      )
   )
   ?indices
)

(deffunction asociacionHeuristica::sort-by-sala (?obras)
   (bind ?len (length$ ?obras))
   (bind ?sorted ?obras)
   
   ; Bucle exterior
   (bind ?i 1)
   (while (<= ?i (- ?len 1))
      ; Bucle interior
      (bind ?j (+ ?i 1))
      (while (<= ?j ?len)
         (bind ?obra1 (nth$ ?i ?sorted))
         (bind ?obra2 (nth$ ?j ?sorted))
         (bind ?sala1 (send ?obra1 get-Sala))
         (bind ?sala2 (send ?obra2 get-Sala))
         
         ; Si la sala1 es mayor que sala2, intercambiar obras
         (if (> ?sala1 ?sala2)
            then
            (bind ?sorted (replace$ ?sorted ?i ?i ?obra2))
            (bind ?sorted (replace$ ?sorted ?j ?j ?obra1))
         )
         (bind ?j (+ ?j 1))
      )
      (bind ?i (+ ?i 1))
   )
   ?sorted
)

(deffunction asociacionHeuristica::sort-by-prioridad (?obras)
   (bind ?len (length$ ?obras))
   (bind ?sorted ?obras)
   
   (bind ?i 1)
   (while (<= ?i (- ?len 1))
      (bind ?j (+ ?i 1))
      (while (<= ?j ?len)
         (bind ?obra1 (nth$ ?i ?sorted))
         (bind ?obra2 (nth$ ?j ?sorted))
         (bind ?prioridad1 (fact-slot-value ?obra1 Prioridad))
         (bind ?prioridad2 (fact-slot-value ?obra2 Prioridad))
         
         ; Ordenar de mayor a menor (>) prioridad
         (if (< ?prioridad1 ?prioridad2)
            then
            (bind ?sorted (replace$ ?sorted ?i ?i ?obra2))
            (bind ?sorted (replace$ ?sorted ?j ?j ?obra1))
         )
         (bind ?j (+ ?j 1))
      )
      (bind ?i (+ ?i 1))
   )
   ?sorted
)

;; 6. Reglas
;; (a) Módulos de preguntas.
(defrule getInput::InicializarDatosVisita
    (declare (salience 10))
    =>
    (assert (datosVisita 
        (Npersonas_visita 0)
        (Conocimiento_visita 0)
        (Ndias_visita 0)
        (Duracion_visita 0)
        (Hay_peques_visita FALSE)
    ))
    (assert (preferenciasVisita))
)

(defrule getInput::preguntaNumeroPersonas
    (declare (salience 9))
    ?fact <- (datosVisita (Npersonas_visita 0))
    =>
    (bind ?pregunta "¿Cuantas personas van a visitar el museo? ")
    (bind ?respuesta (pregunta_numero ?pregunta))
    (modify ?fact (Npersonas_visita ?respuesta))
)

(defrule getInput::pregunta_peques
    (declare (salience 8))
    ?fact <- (datosVisita (Hay_peques_visita FALSE)) 
    (not (peques_preguntado))
    =>
    (bind ?pregunta "¿Van a ir niños pequeños? ")
    (bind ?respuesta (pregunta_boolean ?pregunta))
    (modify ?fact (Hay_peques_visita ?respuesta))
    (assert (peques_preguntado))
)

(defrule getInput::Ndias_visita
    (declare (salience 7))
    ?fact <- (datosVisita (Ndias_visita 0))
    =>
    (bind ?pregunta "¿Cuantos dias va a durar la visita? [1-2]")
    (bind ?respuesta (pregunta_numero_con_rango ?pregunta 1 2))
    (modify ?fact (Ndias_visita ?respuesta))
)

(defrule getInput::Duracion_visita
    (declare (salience 6))
    ?fact <- (datosVisita (Duracion_visita 0))
    =>
    (bind ?pregunta "¿Cuantas horas por dia va a durar la visita? [1-4]")
    (bind ?respuesta (pregunta_numero_con_rango ?pregunta 1 4))
    (modify ?fact (Duracion_visita ?respuesta))
)

(defrule getInput::pregunta_conocimiento
    (declare (salience 5))
    ?fact <- (datosVisita (Conocimiento_visita 0))
    =>
     (printout t "---------------------------------------------------------------------" crlf)
     (printout t "---------------------------------------------------------------------" crlf)
     
     (bind ?puntuacion  0)
	(bind ?formatos (create$ "Si" "No"))
	(bind ?respuesta (pregunta_opcion_unica "¿Conoces 'La Gioconda' de Leonardo Da Vinci?" ?formatos))
	(if (= ?respuesta 1) then (bind ?puntuacion (+ 1 ?puntuacion )))
   
     (bind ?formatos (create$ "Si" "No"))
	(bind ?respuesta (pregunta_opcion_unica "¿Conoces 'Las Meninas' de Velazquez?" ?formatos))
	(if (= ?respuesta 1) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ "Theodore Gericault" "Johannes_Vermeer"  "Pablo Picasso" "Salvador Dali"))
	(bind ?respuesta (pregunta_opcion_unica "¿Qué autor pinto 'La encajera'?" ?formatos))
	(if (= ?respuesta 2) then (bind ?puntuacion (+ 1 ?puntuacion )))
     
     (bind ?formatos (create$ "La ultima Cena" "La persistencia de la memoria" "La terraza del café por la noche" "Las Meninas"))
	(bind ?respuesta (pregunta_opcion_unica "¿Cuál de estas obras es De Van Gogh?" ?formatos))
	(if (= ?respuesta 3) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ "Post Impresionismo" "Egipcio" "Romantico" "Renacimiento"))
	(bind ?respuesta (pregunta_opcion_unica "¿Qué estilo tiene la obra 'La noche estrellada'?" ?formatos))
	(if (= ?respuesta 1) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ "Siglo XV" "Siglo XVI" "Siglo XVII" "Siglo XVIII"))
	(bind ?respuesta (pregunta_opcion_unica "¿De que siglo es la obra 'Las Meninas' de Velazquez?" ?formatos))
	(if (= ?respuesta 3) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ "Fantastico" "Mitologico" "Paisaje"))
	(bind ?respuesta (pregunta_opcion_unica "¿Qué temática tiene 'Los girasloes' de Van Gogh?" ?formatos))
	(if (= ?respuesta 3) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ "La Gioconda" "EL nacimiento de Venus" "La noche estrellada" "La momia"))
	(bind ?respuesta (pregunta_opcion_unica "¿En cual de estas obras se desconoce el autor?" ?formatos))
	(if (= ?respuesta 4) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ "El Beso" "El Grito" "Leon de Monzon" "El Tahur"))
	(bind ?respuesta (pregunta_opcion_unica "¿Qué obra pertnece al Expresionsimo?" ?formatos))
	(if (= ?respuesta 2) then (bind ?puntuacion (+ 1 ?puntuacion )))

     (bind ?formatos (create$ " Un fusilamiento" "Un desalojo" "Un cumpleaños" "Un bombardeo" ))
	(bind ?respuesta (pregunta_opcion_unica "¿A que hace referencia el Guernica?" ?formatos))
	(if (= ?respuesta 4) then (bind ?puntuacion (+ 1 ?puntuacion )))


    (modify ?fact (Conocimiento_visita ?respuesta))
)

(defrule getInput::preguntaPreferencias
    (declare (salience 4))
    ?fact <- (datosVisita (Tematica $?tematicas) (Epoca $?epocas) (Estilo $?estilos) (Pintor $?pintores))
    (not (preferencias_preguntadas))
    =>
    ;; 1. Preguntar si el usuario tiene alguna preferencia general
    (bind ?pregunta "¿Tiene alguna preferencia en cuanto a las obras? ")
    (bind ?respuesta (pregunta_boolean ?pregunta))
    
    (if (eq ?respuesta TRUE) then
        ;; 2. Preguntar por cada tipo de preferencia
        
        (bind ?tematica nil)
        (bind ?epoca nil)
        (bind ?estilo nil)
        (bind ?pintor nil)

        ; 2.1. Temática
        (bind ?pregunta "¿Tiene alguna preferencia en cuanto a la temática de las obras? ")
        (bind ?respuestaTematica (pregunta_boolean ?pregunta))
     (if (eq ?respuestaTematica TRUE) then
     (bind $?allTematicas (find-all-instances ((?inst Tematica)) TRUE))
     (bind $?tematicas (create$))
     
     ; Recolectar nombres de temáticas
     (progn$ (?tematica ?allTematicas)
          (bind ?nombre (send ?tematica get-Nombre)) 
          (bind $?tematicas (insert$ $?tematicas (+ (length$ $?tematicas) 1) ?nombre))
     )

     ; Mostrar opciones y obtener selección
     (bind $?indices_tematicas (pregunta_opcion_multiple "Tematicas que prefiere ver:" $?tematicas))

     ; Procesar selecciones para el hecho
     (bind $?preferencias_tematicas (create$))
     (if (> (length$ $?indices_tematicas) 0) then
          (foreach ?i $?indices_tematicas
               (bind ?tematica (nth$ ?i $?allTematicas))
               (bind $?preferencias_tematicas (create$ $?preferencias_tematicas ?tematica))
          )
     )
     (bind ?tematica $?preferencias_tematicas)
     )
        (readline)

          ;; 2.2. Época
          (bind ?pregunta "¿Tiene alguna preferencia en cuanto a la época de las obras? ")
          (bind ?respuestaEpoca (pregunta_boolean ?pregunta))

          (if (eq ?respuestaEpoca TRUE) then
          (bind $?allEpocas (find-all-instances ((?inst Epoca)) TRUE))
          (bind $?epocas (create$))
          
          (progn$ (?epoca ?allEpocas)
               (bind ?nombre (send ?epoca get-Nombre))
               (bind $?epocas (insert$ $?epocas (+ (length$ $?epocas) 1) ?nombre))
          )
          
          (bind $?indices_epoca (pregunta_opcion_multiple "Epocas que prefiere ver:" $?epocas))
          
          (bind $?preferencias_epoca (create$))
          (if (> (length$ $?indices_epoca) 0) then
               (foreach ?i $?indices_epoca
                    (bind ?epoca (nth$ ?i $?allEpocas))
                    (bind $?preferencias_epoca (create$ $?preferencias_epoca ?epoca))
               )
          )
          (bind ?epoca $?preferencias_epoca)
          )

        (readline)
        
          ;; 2.3. Estilo
          (bind ?pregunta "¿Tiene alguna preferencia en cuanto al estilo de las obras?")
          (bind ?respuestaEstilo (pregunta_boolean ?pregunta))
          (if (eq ?respuestaEstilo TRUE) then
               (bind $?allEstilos (find-all-instances ((?inst Estilo)) TRUE))
               (bind $?estilos (create$))
               
               (progn$ (?estilo ?allEstilos)
                    (bind ?nombre (send ?estilo get-Nombre))
                    (bind $?estilos (insert$ $?estilos (+ (length$ $?estilos) 1) ?nombre))
               )
               
               (bind $?indices_estilos (pregunta_opcion_multiple "Estilos que prefiere ver:" $?estilos))
               
               (bind $?preferencias_estilo (create$))
               (if (> (length$ $?indices_estilos) 0) then
                    (foreach ?i $?indices_estilos
                         (bind ?estilo (nth$ ?i $?allEstilos))
                         (bind $?preferencias_estilo (create$ $?preferencias_estilo ?estilo))
                    )
               )
               (bind ?estilo $?preferencias_estilo)
          )

          (readline)

          ;; 2.4. Pintor
          (bind ?pregunta "¿Tiene alguna preferencia en cuanto al pintor de las obras?")
          (bind ?respuestaPintor (pregunta_boolean ?pregunta))
          (if (eq ?respuestaPintor TRUE) then
               (bind $?allPintores (find-all-instances ((?inst Pintor)) TRUE))
               (bind $?pintores (create$))
               
               (progn$ (?pintor $?allPintores)
                    (bind ?nombre (send ?pintor get-Nombre))
                    (bind $?pintores (insert$ $?pintores (+ (length$ $?pintores) 1) ?nombre))
               )
               
               (bind $?indices_pintores (pregunta_opcion_multiple "Pintores que prefiere ver:" $?pintores))
               
               (bind $?preferencias_pintor (create$))
               (if (> (length$ $?indices_pintores) 0) then
                    (foreach ?i $?indices_pintores
                         (bind ?pintor (nth$ ?i $?allPintores))
                         (bind $?preferencias_pintor (create$ $?preferencias_pintor ?pintor))
                    )
               )
               (bind ?pintor $?preferencias_pintor)
          )
        (readline)
        
        (modify ?fact (Tematica ?tematica) (Epoca ?epoca) (Estilo ?estilo) (Pintor ?pintor))

    else 
        (modify ?fact (Tematica nil) (Epoca nil) (Estilo nil) (Pintor nil))
    )
    
    (assert (preferencias_preguntadas))
    
    ;; 3. Enfocar en el módulo de abstracción para procesar las preferencias
    (focus abstraccion)
)

;; Reglas de abstracción 
(defrule abstraccion::abstraccionGrupo
    (declare (salience 10))
    ?fact <- (datosVisita (Npersonas_visita ?n))
    
    =>
    (if (= ?n 1) then
        (bind ?n-categoria "Individual")
    else 
        (if (<= ?n 3) then
            (bind ?n-categoria "Pequeño")
        else 
            (if (<= ?n 6) then
                (bind ?n-categoria "Mediano")
            else
                (bind ?n-categoria "Grande")
            )
        )
    )
    ;(printout t "Abstracion grupo" crlf)
    (bind ?visita (make-instance visita of Visita))
    (send ?visita put-Npersonas_visita ?n-categoria)
)

(defrule abstraccion::abstraccionConocimiento
    (declare (salience 9))
    ?fact <- (datosVisita (Conocimiento_visita ?nivel))
    (not (conocimientoAbstraido))
    ?visita <- (object (is-a Visita))
    =>
    (bind ?c-categoria (if (< ?nivel 3) then "Poco" else (if (< ?nivel 7) then "Medio" else "Mucho")))
    (send ?visita put-Conocimiento_visita ?c-categoria)
    ;(printout t "Abstracion conocimiento" crlf)
    (assert (conocimientoAbstraido))
)

(defrule abstraccion::abstraccionDiasVisita
    (declare (salience 8))
    ?fact <- (datosVisita (Ndias_visita ?d))
    (not (diasAbstraidos))
    ?visita <- (object (is-a Visita))
    =>
    (send ?visita put-Ndias_visita ?d)
    (assert (diasAbstraidos))
)

(defrule abstraccion::abstraccionDuracionVisita
    (declare (salience 7))
    ?fact <- (datosVisita (Duracion_visita ?h))
    (not (duracionAbstraida))
    ?visita <- (object (is-a Visita))
    =>
    (send ?visita put-Duracion_visita ?h)
    (assert (duracionAbstraida))
)

(defrule abstraccion::abstraccionPreferenciasVisita
    (declare (salience 5))
    ?fact <- (datosVisita 
                (Tematica $?t) 
                (Epoca $?e) 
                (Estilo $?es) 
                (Pintor $?p))
    (not (preferenciasAbstraidas))
    ?visita <- (object (is-a Visita))
    =>
    (bind ?preferencia (make-instance [preferencia] of Preferencia))
    
    (if (> (length$ $?t) 0) then
        (send ?preferencia put-preferencia_de_tematica $?t))
    
    (if (> (length$ $?e) 0) then
        (send ?preferencia put-preferencia_de_epoca $?e))
    
    (if (> (length$ $?es) 0) then
        (send ?preferencia put-preferencia_de_estilo $?es))
    
    (if (> (length$ $?p) 0) then
        (send ?preferencia put-preferencia_de_pintor $?p))
    
    (send ?visita put-vista_tiene_preferencia ?preferencia)
    (assert (preferenciasAbstraidas))
)

(defrule abstraccion::abstraccionFinal
    (declare (salience 4))
    =>
    (focus asociacionHeuristica)
)

;; Reglas de asociación heurística
(defrule asociacionHeuristica::buscar-preferencias-visita
    (declare (salience 10))
    ?visita <- (object (is-a Visita))
    =>
    (do-for-all-instances ((?obra Obra)) TRUE
        (bind ?prioridad 0)
        (bind ?duracion_base 0.08) ;5 minutos por obra
        
        ; Ajustar duración por complejidad
        (bind ?complejidad (send ?obra get-Complejidad))
        (bind ?duracion (* ?duracion_base (/ ?complejidad 1.5)))
        
        ; Ajustar por conocimiento
        (bind ?conocimiento (send ?visita get-Conocimiento_visita))
        (bind ?factor_conocimiento (if (eq ?conocimiento "Poco") then 0.7
                                  else (if (eq ?conocimiento "Medio") then 1.0
                                       else 1.3)))
        (bind ?duracion (* ?duracion ?factor_conocimiento))
        
        ; Ajustar por tamaño del grupo
        (bind ?tam_grupo (send ?visita get-Npersonas_visita))
        (bind ?factor_grupo (if (eq ?tam_grupo "Individual") then 1.0
                           else (if (eq ?tam_grupo "Pequeño") then 1.2
                                else (if (eq ?tam_grupo "Mediano") then 1.4
                                     else 1.6))))
        (bind ?duracion (* ?duracion ?factor_grupo))
        
        ; Ajustar si hay niños
        (if (eq (send ?visita get-Hay_peques_visita) TRUE) 
        then (bind ?duracion (* ?duracion 2.0)))
        
        ; Obtener preferencias
        (bind $?preferencias (send ?visita get-vista_tiene_preferencia))
        (if (> (length$ $?preferencias) 0) then
            (bind ?preferencia (nth$ 1 $?preferencias))
            
            ; Obtener listas de preferencias
            (bind $?pref_epoca (send ?preferencia get-preferencia_de_epoca))
            (bind $?pref_estilo (send ?preferencia get-preferencia_de_estilo))
            (bind $?pref_pintor (send ?preferencia get-preferencia_de_pintor))
            (bind $?pref_tematica (send ?preferencia get-preferencia_de_tematica))

            ; Verificar época - 5 puntos por cada coincidencia
            (if (neq $?pref_epoca (create$)) then
                (bind ?obra_epoca (send ?obra get-obra_tiene_epoca))
                (if (member$ ?obra_epoca $?pref_epoca) then
                    (bind ?prioridad (+ ?prioridad 5))))
            
            ; Verificar estilo - 5 puntos por cada coincidencia
            (if (neq $?pref_estilo (create$)) then
                (bind ?obra_estilo (send ?obra get-obra_tiene_estilo))
                (if (member$ ?obra_estilo $?pref_estilo) then
                    (bind ?prioridad (+ ?prioridad 5))))
            
            ; Verificar pintor - 5 puntos por cada coincidencia
            (if (neq $?pref_pintor (create$)) then
                (bind ?obra_pintor (send ?obra get-obra_tiene_pintor))
                (if (member$ ?obra_pintor $?pref_pintor) then
                    (bind ?prioridad (+ ?prioridad 5))))
            
            ; Verificar temática - 5 puntos por cada coincidencia
            (if (neq $?pref_tematica (create$)) then
                (bind ?obra_tematica (send ?obra get-obra_tiene_tematica))
                (if (member$ ?obra_tematica $?pref_tematica) then
                    (bind ?prioridad (+ ?prioridad 5))))
        )

        ; Añadir puntos por importancia
        (bind ?importancia (send ?obra get-Importancia))
        (if (eq ?importancia 3) then 
            (bind ?prioridad (+ ?prioridad 5))
        else (if (eq ?importancia 2) then 
            (bind ?prioridad (+ ?prioridad 3))
        else (if (eq ?importancia 1) then 
            (bind ?prioridad (+ ?prioridad 1))
        )))

        ; Crear hecho con prioridad
        (assert (Obra_Preferente 
            (Obra ?obra)
            (Prioridad ?prioridad)
            (Sala (send ?obra get-Sala))
            (Duracion ?duracion)))
    )
)

(defrule asociacionHeuristica::crear-y-ordenar-ruta
    (declare (salience 8))
    ?visita <- (object (is-a Visita) (Duracion_visita ?tiempo_visita))
    =>
    ; 1. Obtener obras ordenadas por prioridad
    (bind $?prioridades (find-all-facts ((?f Obra_Preferente)) TRUE))
    (bind $?prioridades-ordenadas (sort-by-prioridad $?prioridades))
    (bind $?ruta (create$))
    
    ; 2. Calcular tiempo disponible
    (bind ?tiempo_numerico (send ?visita get-Duracion_visita))
    
    (bind ?tiempoRestante ?tiempo_numerico)
    ;(printout t "Creando ruta con tiempo: " ?tiempoRestante " horas" crlf)

    ; 3. Crear ruta inicial con obras prioritarias
    (foreach ?obra $?prioridades-ordenadas
        (if (> ?tiempoRestante 0) then 
            (bind ?duracion (fact-slot-value ?obra Duracion))
            (bind ?obra_actual (fact-slot-value ?obra Obra))
            (if (<= ?duracion ?tiempoRestante) then
                (bind ?tiempoRestante (- ?tiempoRestante ?duracion))
                (bind $?ruta (insert$ $?ruta (+ (length$ $?ruta) 1) ?obra_actual))
            )
        )
    )
    
    ; 4. Ordenar ruta final por sala
    (bind $?rutaOrdenada (sort-by-sala $?ruta))
    (assert (Ruta (Obras $?rutaOrdenada)))
    (focus showResultado)
)

(defrule asociacionHeuristica::crear-rutas-diarias
    (declare (salience 8))
    ?visita <- (object (is-a Visita) 
                      (Duracion_visita ?tiempo_por_dia)
                      (Ndias_visita ?num_dias))
    =>
    ; 1. Obtener obras ordenadas por prioridad
    (bind $?prioridades (find-all-facts ((?f Obra_Preferente)) TRUE))
    (bind $?prioridades-ordenadas (sort-by-prioridad $?prioridades))
    (bind $?obras_disponibles $?prioridades-ordenadas)
    
    ; 2. Crear una ruta para cada día
    (loop-for-count (?dia 1 ?num_dias)
        (bind $?ruta_dia (create$))
        (bind ?tiempo_restante ?tiempo_por_dia)
        
        ; 3. Seleccionar obras para este día
        (bind $?obras_temp $?obras_disponibles)
        (foreach ?obra $?obras_temp
            (if (> ?tiempo_restante 0) then 
                (bind ?duracion (fact-slot-value ?obra Duracion))
                (bind ?obra_actual (fact-slot-value ?obra Obra))
                (if (<= ?duracion ?tiempo_restante) then
                    (bind ?tiempo_restante (- ?tiempo_restante ?duracion))
                    (bind $?ruta_dia (insert$ $?ruta_dia 
                                            (+ (length$ $?ruta_dia) 1) 
                                            ?obra_actual))
                    ; Eliminar obra usada de disponibles
                    (bind $?obras_disponibles 
                          (delete-member$ $?obras_disponibles ?obra))
                )
            )
        )
        
        ; 4. Ordenar ruta del día por sala
        (bind $?ruta_dia_ordenada (sort-by-sala $?ruta_dia))
        
        ; 5. Crear hecho para la ruta del día
        (assert (Ruta_Diaria 
                 (Dia ?dia)
                 (Obras $?ruta_dia_ordenada)))
    )
    (focus showResultado)
)

;; Reglas de impresión del resultado
(defrule showResultado::iniciar-contador
    (declare (salience 20))
    (not (exists (contador)))
    =>
    (assert (contador (count 1)))
)

(defrule showResultado::imprimir-resultado-dia
    (declare (salience 10))
    ?contador <- (contador (count ?n))
    (exists (Ruta_Diaria (Dia ?n)))
    ?ruta <- (Ruta_Diaria (Dia ?n) (Obras $?obras))
    =>
    (printout t crlf)
    (printout t "******************** Dia " ?n " ********************" crlf)
    (printout t "---------------- Sala - Obra - Tiempo ---------------" crlf)
    (printout t crlf)
    
    (foreach ?obra $?obras
        (bind ?sala (send ?obra get-Sala))
        (bind ?nombre (send ?obra get-Nombre))
        
        (bind ?duracion 0)
        (do-for-all-facts ((?pref Obra_Preferente)) 
            (eq ?obra ?pref:Obra)
            (bind ?duracion ?pref:Duracion))
        (bind ?duracion_min (integer (* ?duracion 60)))
        
        (format t "Sala: %d - Obra: %s - Duracion: %d minutos%n"
                ?sala ?nombre ?duracion_min)
    )
    
    (modify ?contador (count (+ ?n 1)))
)