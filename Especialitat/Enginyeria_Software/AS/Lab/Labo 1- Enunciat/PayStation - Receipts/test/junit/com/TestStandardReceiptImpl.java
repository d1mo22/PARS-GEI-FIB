package junit.com;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestStandardReceiptImpl {
	public StandardReceiptImpl r= new StandardReceiptImpl( 34 );
	@Test
	public void testPrintStandardReceipt() {
		 
		 String receiptContent = "----------------------------------";		
		 receiptContent = receiptContent + "\n";
		 receiptContent = receiptContent + "-------- PARKING RECEIPT --------";
		 receiptContent = receiptContent + "\n";
		 receiptContent = receiptContent + "         Value " + 34 + " minutes";
		 receiptContent = receiptContent + "\n";
		 receiptContent = receiptContent + "STANDARD RECEIPT";
		 receiptContent = receiptContent + "----------------------------------";
		 assertEquals(receiptContent, r.print()); 
	}

}
