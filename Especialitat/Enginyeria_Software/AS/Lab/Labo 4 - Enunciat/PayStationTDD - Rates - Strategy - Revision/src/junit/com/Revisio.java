package junit.com;

public class Revisio extends State {

    @Override
    void revised(PayStationImpl ps) {
        State newR = new Revised();
        ps.changeState(newR);
    }

    @Override
    void revisio(PayStationImpl ps) {

    }

    @Override
    String getState() {
        return "REVISION";
    }

}
