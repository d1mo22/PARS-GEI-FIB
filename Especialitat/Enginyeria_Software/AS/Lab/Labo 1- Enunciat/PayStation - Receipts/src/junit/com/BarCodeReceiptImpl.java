package junit.com;

public class BarCodeReceiptImpl extends ReceiptImpl {

	  public BarCodeReceiptImpl(int value) {
        super(value);
      }

      @Override
	  public String printEspecific(String receiptContent) {
	    for (int i=0; i<value; i++) {
	      receiptContent = receiptContent + "|"; }
	      receiptContent = receiptContent + "\n";
	      receiptContent = receiptContent + "BARCODE RECEIPT";
	      receiptContent = receiptContent + "----------------------------------";
          return receiptContent;
        }
	  }

