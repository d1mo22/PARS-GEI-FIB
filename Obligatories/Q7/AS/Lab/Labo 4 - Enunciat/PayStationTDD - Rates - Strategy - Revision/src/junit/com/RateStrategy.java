package junit.com;
/** The strategy for calculating parking rates.

  Responsibilities:
			
  1) Calculate the parking time for a given payment;

  Instances of this interface plays the Strategy role
  in the Strategy design pattern.
 
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
public interface RateStrategy {
  /**
   return the number of minutes parking time the provided 
   payment is valid for.  
   @param amount payment in some currency.
   @return number of minutes parking time.
   */
  public int calculateTime( int amount );
}

