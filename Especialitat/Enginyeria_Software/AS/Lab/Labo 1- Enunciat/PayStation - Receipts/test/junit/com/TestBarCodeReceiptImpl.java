package junit.com;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestBarCodeReceiptImpl {
	public BarCodeReceiptImpl r= new BarCodeReceiptImpl( 34 );

	@Test
	public void testPrintBarCodeReceipt() {
		 
		 String receiptContent = "----------------------------------";		
		 receiptContent = receiptContent + "\n";
		 receiptContent = receiptContent + "-------- PARKING RECEIPT --------";
		 receiptContent = receiptContent + "\n";
		 receiptContent = receiptContent + "         Value " + 34 + " minutes";
		 receiptContent = receiptContent + "\n";
		 for (int i=0; i<34; i++) {
				receiptContent = receiptContent + "|";
		 }
		 receiptContent = receiptContent + "\n";
		 receiptContent = receiptContent + "BARCODE RECEIPT";
		 receiptContent = receiptContent + "----------------------------------";
		 assertEquals(receiptContent, r.print()); 
	}

}
