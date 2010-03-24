package com.banandroid.curlretsjni;

public class listingRecord {

	public String ListPrice;
	public String Address;
	public String ListingID;
	public String Bedrooms;
	public String Baths;
	public String YearBuilt;
	public String LivingArea;
	public String AgentID;
	public String SqFt;
	public String County;
	public String Garage;
	/*
	 * 	AgentID	Baths	Bedrooms	Board	City	CloseDate	
	 * ClosePrice	ContractDate	County	Garage	ListingID	
	 * ListDate	ListPrice	LivingArea	ModificationTimestamp	
	 * Rooms	SqFt	State	Status	StreetDirection	StreetName	
	 * StreetNumber	Unit	YearBuilt	ZipCode
	 */
	
	public String print() {
		String output = "";
		output = this.Address;
		return output;
	}
	
	public String print2() {
		String output = "";
		output = this.Bedrooms + " beds, " + this.Baths + " baths, for $" + this.ListPrice;
		return output;
	}
	
	public String printVerbose() {
		String output = "";
		output = this.Bedrooms + " beds, " + this.Baths + " baths, at " + this.Address + " for $" + this.ListPrice;
		return output;
	}

	public String printDetails() {
		String output = "";
		output = 
			"ListPrice: " + this.ListPrice + "\n" +
			"Address: " +	this.Address + "\n" +
			"ListingID: " +	this.ListingID + "\n" +
			"Bedrooms: " +	this.Bedrooms + "\n" +
			"Baths: " +		this.Baths + "\n" +
			"YearBuilt: " + this.YearBuilt + "\n" +
			"LivingArea: " +this.LivingArea + "\n" +
			"AgentID: "	+	this.AgentID + "\n" +
			"SqFt: " +		this.SqFt + "\n" +
			"County: " +	this.County + "\n" +
			"Garage: " +	this.Garage;
		
		return output;
	}
}

