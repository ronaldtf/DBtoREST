package main.java.rest;

import java.util.Vector;

import org.json.JSONArray;
import org.json.JSONObject;

import main.java.db.table.Column;

public class JSONGenerator {
	/**
	 * Create a JSON document given a list of values
	 * @param root			Root tag
	 * @param elements		List of values to generate the JSON document
	 * @return				JSON document in text format
	 */
	public static String getJson(final String root, final Vector<String> elements) {
		JSONObject jsonObject = new JSONObject();
		JSONArray jsonArray = new JSONArray(elements);
		jsonObject.put(root, jsonArray);

		// Return a formatted String
		return jsonObject.toString(2);
	}

	/**
	 * Create a JSON document given a database table
	 * @param root		Root tag
	 * @param table		Table values
	 * @return			JSON document in text format
	 */
	public static String getJson(final String root, final Column table) {	
		// Create a with the values and initialize it
		int size = table.getValues().size();
		Vector<JSONArray> elements = new Vector<JSONArray>(size);
		for (int i = 0; i<size; ++i) {
			elements.addElement(new JSONArray());
		}
		
		// Fill the vector elements with the elements of each Column
		// Each element of the vector corresponds to a row of the table
		Column row = table;
		Vector<String> values;
		do {
			values = row.getValues();
			int index = 0;
			// Go through all the values in the row and put them each in
			// a different array (list)
			for (String element : values) {
				JSONObject jsonObject = new JSONObject();
				jsonObject.put(row.getColumnName(), element);
				elements.elementAt(index).put(jsonObject);
				++index;
			}
		} while ((row = table.getNeighbor()) != null);
		
		// Create the root object with all the elements
		JSONObject jsonObject = new JSONObject();
		jsonObject.put(root, elements);
		
		// Return the formatted String
		return jsonObject.toString(2);
	}
}
