package junit.com;

import org.junit.*;
import static org.junit.Assert.*;

/** Test cases for the Pay Station system.
 
   This source code is from the book 
     "Flexible, Reliable Software:
       Using Patterns and Agile Development"
     published 2010 by CRC Press.
   Author: 
     Henrik B Christensen 
     Department of Computer Science
     Aarhus University
   
   Please visit http://www.baerbak.com/ for further information.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/
public class TestPayStation {
  PayStationImpl ps;
  /** Fixture for pay station testing. */
  @Before
  public void setUp() {
    ps = new PayStationImpl( new LinearRateStrategy(), new Revised() );
  }

  
  @Test 
  public void testInitiallyRevised() {
    assertEquals("REVISED", ps.getState());
  }
  
  @Test 
  public void testRevisedWhenRevised() {
	ps.revised();
	assertEquals("REVISED", ps.getState());
	ps.revised();
    assertEquals("There is not a state change", "REVISED", ps.getState());
  }
  
  
  @Test 
  public void testRevisedWhenRevision() {
	ps.revision();
	assertEquals("REVISION", ps.getState());
	ps.revised();
    assertEquals("REVISED", ps.getState());
  }
  
  @Test 
  public void testRevisionWhenRevised() {
	ps.revised(); 
	assertEquals("REVISED", ps.getState());
	ps.revision();
    assertEquals("REVISION", ps.getState());
  }
  
  @Test 
  public void testRevisionWhenRevision() {
	ps.revision();
	assertEquals("REVISION", ps.getState());
	ps.revision();
    assertEquals("There is not a state change","REVISION", ps.getState());
  }
  
}
