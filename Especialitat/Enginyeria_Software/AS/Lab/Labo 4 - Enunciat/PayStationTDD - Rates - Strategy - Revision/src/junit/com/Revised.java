package junit.com;

public class Revised extends State {
    @Override
    void revised(PayStationImpl ps) {

    }

    @Override
    void revisio(PayStationImpl ps) {
        State newR = new Revisio();
        ps.changeState(newR);
    }

    @Override
    String getState() {
        return "REVISED";
    }

}
