package junit.com;

public class ProgressiveRate implements RateStrategy {
    public int calculateTime(int insertedSoFar) throws IllegalCoinException {
        int time = 0;
        if ( insertedSoFar >= 150+200 ) { // from 2nd hour onwards
            insertedSoFar -= 350;
            time = 120 /*min*/ + insertedSoFar / 5;
        } else if ( insertedSoFar >= 150 ) { // from 1st to 2nd hour
            insertedSoFar -= 150;
            time = 60 /*min*/ + insertedSoFar * 3 / 10;
        } else { // up to 1st hour
            time = insertedSoFar * 2 / 5;
        }
        return time;
    }
}
