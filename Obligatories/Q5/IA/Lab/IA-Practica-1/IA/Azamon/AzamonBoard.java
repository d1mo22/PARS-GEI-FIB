package IA.Azamon;

import java.util.*;

/**
 * Clase que representa el estado del problema de Azamon
 */
public class AzamonBoard {
    // Nº of packages
    private int nPackages = 100;

    // Nº of offers
    private final int nOffers;

    // List with the packages
    private final Paquetes packages;

    // List with the offers
    private final Transporte transport;

    // Package assignment
    /**
     * Paquete (índice) -> Oferta (valor)
     */
    private int[] packageAssignment;

    /**
     * Peso restante de las ofertas
     */
    private double[] weightLeft;

    // Total price
    /**
     * Precio total de la asignación
     */
    private double totalPrice;

    // Total happiness
    /**
     * Felicidad total de la asignación
     */
    private double happinessPrice;
    /** Happiness constant: la importancia a la hora de calcular el heurístico */
    private double happinessConstant = 1;

    // Constructors
    /**
     * Constructor de la clase AzamonBoard
     * @param p   Paquetes a asignar
     * @param t   Transportes a asignar
     * @param ini Estado inicial a asignar (0 -> Prioridad, 1 -> Peso)
     */
    public AzamonBoard(Paquetes p, Transporte t, int ini) {
        nPackages = p.size();
        nOffers = t.size();
        packages = p;
        transport = t;
        packageAssignment = new int[nPackages];
        weightLeft = new double[nOffers];
        totalPrice = 0.0;
        happinessPrice = 0.0;

        for (int i = 0; i < nOffers; i++) {
            // Initialize free space with the maximum weight of each offer
            weightLeft[i] = t.get(i).getPesomax();
        }
        for (int i = 0; i < nPackages; i++) {
            // No package assigned = -1
            packageAssignment[i] = -1;
        }
        // Generación del estado inicial: (ini == 0) inicializa los paquetes por prioridad.
        // Generación del estado inicial: (ini == 1) inicializa los paquetes por peso.
        if (ini == 0) packages.sort(new PackageComparatorPriority());
        else if (ini == 1) {
            packages.sort(new PackageComparatorWeight());
            transport.sort(new OfferComparator());
            // Hacemos un bucle para asignar el nuevo peso libre de cada oferta
            for (int i = 0; i < nOffers; i++) {
                weightLeft[i] = t.get(i).getPesomax();
            }
        }
        if (!azamonBoardIni(packageAssignment.clone(), weightLeft.clone(), 0)) {
            System.out.println("No se ha podido asignar los paquetes");
            return;
        }
        calculatePriceHappiness();
        calculatePrice();
    }

    public AzamonBoard(AzamonBoard board) {
        nPackages = board.getNPackages();
        nOffers = board.getNOffers();
        packages = board.getPackages();
        transport = board.getTransport();
        packageAssignment = board.getPackageAssignment().clone();
        weightLeft = board.getWeightLeft().clone();
        totalPrice = board.getTotalPrice();
        happinessPrice = board.getHappinessPrice();
        happinessConstant = board.getHappinessConstant();
    }

    /**
     * Estado inicial 1
     * Funcion que genera un estado inicial a partir de un backtracking
     * ("óptima")
     *
     * @param assig Asignacion de los paquetes
     * @param free  Peso libre de las ofertas
     * @param i     Indice del paquete
     * @return Booleano que indica si se ha podido asignar los paquetes
     */
    private boolean azamonBoardIni(int[] assig, double[] free, int i) {
        if (i >= nPackages) {
            packageAssignment = assig;
            weightLeft = free;
            return true;
        }

        Paquete p = packages.get(i);

        for (int j = 0; j < nOffers; j++) {
            if (compatible(i, j, free[j])) {
                assig[i] = j;
                free[j] -= p.getPeso();
                if (azamonBoardIni(assig.clone(), free.clone(), i + 1)) {
                    return true;
                } else {
                    assig[i] = -1;
                    free[j] += p.getPeso();
                }
            }
        }
        return false;
    }

    /**
     * Devuelve la lista de paquetes
     *
     * @return Lista de paquetes
     */
    public Paquetes getPackages() {
        return packages;
    }

    public void setHappinessConstant(double happinessConstant) {
        this.happinessConstant = happinessConstant;
    }

    /**
     * Devuelve la lista de ofertas
     *
     * @return Lista de ofertas
     */
    public Transporte getTransport() {
        return transport;
    }

    /**
     * Devuelve el número de paquetes
     *
     * @return Número de paquetes
     */
    public int getNPackages() {
        return nPackages;
    }

    /**
     * Devuelve el número de ofertas
     *
     * @return Número de ofertas
     */
    public int getNOffers() {
        return nOffers;
    }

    /**
     * Devuelve el precio de la asignación actual
     *
     * @return Precio de la asignación actual
     */
    public double getTotalPrice() {
        return totalPrice;
    }

    /**
     * Devuelve la felicidad de la asignación actual
     *
     * @return Felicidad de la asignación actual
     */
    public double getHappinessPrice() {
        return happinessPrice;
    }

    /**
     * Devuelve la importancia de felicidad en el heurístico
     * @return constante de la felicidad
     */
    public double getHappinessConstant() {
        return happinessConstant;
    }

    /**
     * Devuelve la asignación de paquetes
     * @return asignación de paquetes a las ofertas
     */
    public int[] getPackageAssignment() {
        return Arrays.copyOf(packageAssignment, packageAssignment.length);
    }

    /**
     * Devuelve el peso libre de una asignación
     * @return peso libre de una asignación
     */
    public double[] getWeightLeft() {
        return Arrays.copyOf(weightLeft, weightLeft.length);
    }

    /**
     * Función que calcula el precio teniendo en cuenta el factor de la felicidad
     */
    private void calculatePriceHappiness() {
        double sum = 0.0;
        for (int i = 0; i < nPackages; i++) {
            double price = calculatePrice(i, packageAssignment[i]);
            double happiness = calculateHappiness(i, packageAssignment[i]);
            sum += price - (happiness * happinessConstant);
        }
        happinessPrice = sum;
    }

    /**
     * Función que calcula la felicidad según una asignación de un paquete a una oferta
     * @param paquete paquete de la asignación
     * @param oferta oferta a la que hemos asignado el paquete
     * @return diferencia de días entre la prioridad y los días de la oferta
     */
    private double calculateHappiness(int paquete, int oferta) {
        int daysPriority = getDiasPrioridad(packages.get(paquete).getPrioridad()) - 1;
        int daysOffer = transport.get(oferta).getDias();
        // Si la prioridad es 0 o es menor que los días de la oferta, la felicidad es 0
        if (daysPriority == 0 || daysPriority <= daysOffer) {
            return 0;
        }
        // Si la prioridad es 1 y la oferta es de 3 dias, la felicidad es 1
        else {
            return (daysPriority - daysOffer);
        }
    }

    /**
     * Calcula el precio total de la asignacion actual
     */
    private void calculatePrice() {
        double sum = 0.0;
        for (int i = 0; i < nPackages; i++) {
            sum += calculatePrice(i, packageAssignment[i]);
        }
        totalPrice += sum;
    }

    /**
     * Calcula el precio de un paquete asignado a una oferta
     *
     * @param paquete Indice del paquete
     * @param oferta  Índice de la oferta
     * @return Precio del paquete asignado a la oferta
     */
    private double calculatePrice(int paquete, int oferta) {
        double weightPackage = packages.get(paquete).getPeso();
        double storage = getStoreDays(oferta) * 0.25 * weightPackage;
        double delivery = transport.get(oferta).getPrecio() * weightPackage;
        return delivery + storage;
    }

    /**
     * Devuelve los días de prioridad de un paquete
     *
     * @param prioridad Prioridad del paquete
     * @return Días de prioridad del paquete
     */
    private int getDiasPrioridad(int prioridad) {
        return 2*prioridad+1;
    }

    /**
     * Comprueba si un paquete es compatible con una oferta
     *
     * @param paq    Paquete a comprobar
     * @param oferta Oferta a comprobar
     * @param peso   Peso restante de la oferta
     * @return Booleano que indica si el paquete es compatible con la oferta
     */
    private boolean compatible(int paq, int oferta, double peso) {
        Oferta o = transport.get(oferta);
        Paquete p = packages.get(paq);
        boolean days = o.getDias() <= getDiasPrioridad(p.getPrioridad());
        boolean weight = peso >= p.getPeso();
        return days && weight;
    }

    /**
     * Comprueba si un paquete es compatible con una oferta
     *
     * @param paq    Paquete a comprobar
     * @param oferta Oferta a comprobar
     * @return Booleano que indica si el paquete es compatible con la oferta
     */
    public boolean compatible(int paq, int oferta) {
        return compatible(paq, oferta, weightLeft[oferta]);
    }

    private int getStoreDays(int i) {
        return switch (transport.get(i).getDias()) {
            case 3, 4 -> 1;
            case 5 -> 2;
            default -> 0;
        };
    }

    // Debug function: Hace un print del estado
    public void printState() {
        for (int i = 0; i < nOffers; i++) {
            if (weightLeft[i] < 0)
                System.out.println("Peso de la oferta " + i + " negativo!");
        }
    }

    /**
     * Mueve, si se pude, un Paquete de una Oferta a otra
     *
     * @param paquete posicion del Paquete a mover
     * @param oferta  posicion del Oferta a mover
     */
    public void moverPaquete(int paquete, int oferta) {
        // oldOffer: en qué índice de oferta estaba el paquete
        int oldOffer = packageAssignment[paquete];
        // nuevo índice de oferta
        packageAssignment[paquete] = oferta;
        if (oldOffer != -1) {
            weightLeft[oldOffer] += packages.get(paquete).getPeso();
        }

        weightLeft[oferta] -= packages.get(paquete).getPeso();

        double oldPrice = calculatePrice(paquete, oldOffer);
        double newPrice = calculatePrice(paquete, oferta);

        totalPrice += newPrice - oldPrice;

        double oldHappiness = calculateHappiness(paquete, oldOffer);
        double newHappiness = calculateHappiness(paquete, oferta);
        happinessPrice += newPrice - oldPrice - (newHappiness - oldHappiness) * happinessConstant;
    }

    /**
     * Comprueba si se puede hacer un swap entre dos paquetes
     *
     * @param paquete1 posicion del primer Paquete a intercambiar
     * @param paquete2 posicion del segundo Paquete a intercambiar
     * @return Booleano que indica si se puede hacer el swap
     */
    public boolean swapCompatible(int paquete1, int paquete2) {
        double space1 = weightLeft[packageAssignment[paquete1]];
        space1 += packages.get(paquete1).getPeso();
        double space2 = weightLeft[packageAssignment[paquete2]];
        space2 += packages.get(paquete2).getPeso();
        return compatible(paquete1, packageAssignment[paquete2], space2) &&
                compatible(paquete2, packageAssignment[paquete1], space1);
    }

    /**
     * Intercambia dos paquetes de dos ofertas
     *
     * @param paquete1 posicion del primer Paquete a intercambiar
     * @param paquete2 posicion del segundo Paquete a intercambiar
     */
    public void swapPaquetes(int paquete1, int paquete2) {
        int oferta1 = packageAssignment[paquete1];
        int oferta2 = packageAssignment[paquete2];
        double peso1 = packages.get(paquete1).getPeso();
        double peso2 = packages.get(paquete2).getPeso();

        // Actualizamos el precio
        double oldPrice = calculatePrice(paquete1, oferta1) + calculatePrice(paquete2, oferta2);
        double newPrice = calculatePrice(paquete1, oferta2) + calculatePrice(paquete2, oferta1);
        totalPrice += newPrice - oldPrice;

        double oldHappiness = calculateHappiness(paquete1, oferta1) + calculateHappiness(paquete2, oferta2);
        double newHappiness = calculateHappiness(paquete1, oferta2) + calculateHappiness(paquete2, oferta1);
        happinessPrice += newPrice - oldPrice - (newHappiness - oldHappiness) * happinessConstant;

        // Actualizamos la asignacion
        packageAssignment[paquete1] = oferta2;
        packageAssignment[paquete2] = oferta1;

        // Actualizamos el weightLeft
        weightLeft[oferta1] += peso1 - peso2;
        weightLeft[oferta2] += peso2 - peso1;
    }

    /**
     * Comparador de paquetes por prioridad
     */
    static class PackageComparatorPriority implements Comparator<Paquete> {
        public int compare(Paquete p1, Paquete p2) {
            return Integer.compare(p1.getPrioridad(), p2.getPrioridad());
        }
    }

    /**
     * Comparador de paquetes por peso
     */
    static class PackageComparatorWeight implements Comparator<Paquete> {
        public int compare(Paquete p1, Paquete p2){
            return Double.compare(p2.getPeso(), p1.getPeso());

        }
    }

    /**
     * Comparador de ofertas por ratio precio/peso
     */
    static class OfferComparator implements Comparator<Oferta> {
        public int compare(Oferta o1, Oferta o2){
            double oratio1 = o1.getPrecio()/o1.getPesomax();
            double oratio2 = o2.getPrecio()/o2.getPesomax();
            return Double.compare(oratio1, oratio2);

        }
    }
}