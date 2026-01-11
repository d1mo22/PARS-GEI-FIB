package junit.com;

public interface RateStrategy {
    public int calculateTime(int insertedSoFar) throws IllegalCoinException;
}
