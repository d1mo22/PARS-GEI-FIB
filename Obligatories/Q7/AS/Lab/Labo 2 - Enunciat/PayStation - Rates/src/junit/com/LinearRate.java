package junit.com;

public class LinearRate implements RateStrategy{
  public int calculateTime(int insertedSoFar) throws IllegalCoinException {
    return insertedSoFar / 5 * 2;
  }
}
