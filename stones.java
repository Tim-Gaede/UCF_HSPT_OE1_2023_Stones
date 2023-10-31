// UCF HSPT Online (December 2022)
// Java Solution for "Skipping Stones"
// Solution by Chris Gittings

import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class stones 
{
	static String tie = "Tie!", template = " will have more fun!";
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		
		// take in the number of cases
		int tt = scan.nextInt();
		
		// loop through cases
		for(int t = 0; t < tt; t++)
		{
			// storing alice's and bob's information in a list
			ArrayList<Integer> alice = new ArrayList<Integer>(), bob = new ArrayList<Integer>();
			
			// take in Alice's information
			int n = scan.nextInt();
			for(int i = 0; i < n; i++)
				alice.add(scan.nextInt());
			
			// take in Bob's information
			int m = scan.nextInt();
			for(int i = 0; i < m; i++)
				bob.add(scan.nextInt());
			
			// compress the lists 
			compress(alice);
			compress(bob);
			
			// compare the compressed lists and get the answer
			String ans = compare(alice, bob);
				
			// print the answer!
			System.out.println(ans);
		}
		
		scan.close();
	}

	// takes in a list of digits and returns an ordered list with only unique binary digits
	private static void compress(ArrayList<Integer> digits) 
	{
		TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer>();
		
		// fill the map with the digits and their frequencies
		for(int i : digits)
			map.put(i, map.getOrDefault(i, 0) + 1);
		
		// clear the map and we will restore it from scratch
		digits.clear();
		
		Map.Entry<Integer, Integer> entry = map.firstEntry();
		
		// iterate through each entry
		while(entry != null)
		{
			int key = entry.getKey();
			int quant = entry.getValue();
			
			while(quant > 0)
			{
				// if the frequency is odd, this binary digit is on (add it to the list)
				if(quant % 2 == 1)
					digits.add(key);
				
				// update the quantity and digit values
				quant /= 2;
				key++;
				
				// add the next frequency of digits if it exists
				if(map.containsKey(key))
					quant += map.get(key);
			}
			
			// get the next qualifying entry
			entry = map.ceilingEntry(key);
		}
	}
	
	// iterate through the list and return the list that represents the larger binary value
	private static String compare(ArrayList<Integer> alice, ArrayList<Integer> bob) 
	{
		int i = alice.size() - 1, j = bob.size() - 1;
		
		while(i >= 0 && j >= 0)
		{
			// compare the two integers
			// make sure to compare the integers with Integer.compare, 
			// because after 127, Integer start comparing addresses just like any other object
			if(Integer.compare(alice.get(i), bob.get(j)) != 0)
			{
				// if alice has the first larger value, return that alice will have more fun
				if(Integer.compare(alice.get(i), bob.get(j)) > 0) 
					return "Alice" + template;
				// if bob has the first larger value, return that bob will have more fun
				else
					return "Bob" + template;
			}
			
			i--; j--;
		}
		
		// since there are no differences in values for the compared values, 
		// the person who had more fun will be the person with the larger sized list (binary 1 digits)
		if(i < 0 && j < 0) return tie;
		else if(i < 0) return "Bob" + template;
		else return "Alice" + template;
	}
}
