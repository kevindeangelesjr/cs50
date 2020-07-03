/*

Data types
    boolean
    double, float
    char
    int
    List
    Map
    String

Variables
    String title = "CS50";
    int count = 50;
    count +=5;

Conditions
    String title = "ios";
    if (title.equals("ios")) {
        System.out.println("Good choice");
    }
    else {
        System.out.println("Maybe next time");
    }

Arrays
    int[] values = new int[]{ 1, 2, 3 };
    for (int i = 0; i < values.length; i ++){
        System.out.println(i);
    }

Lists - basically dynamically sized array.  Really easy to add and remove values
    List<String> values = new ArrayList<>();
    values.add("one");
    values.add("two");
    for (String value : values) {
        System.out.println(value);
    }

Generics - 'pass a type to another type'
    List<String> strings = new ArrayList<>();
    List<Integer> integers = new ArrayList<>();

Maps - basically a dictionary.  Maps keys to values
    Map<String, String> airports = new HashMap<>();
    airports.put("SFO", "San Francisco");
    airpots.put("BOS", "Boston");
    for (Map.Entry<String, String> e : airports.entrySet()) {
        System.out.println(e.getKey() + ": " + e.getValue());
    }
*/

// Class - struct with functions (methods)
public class Person {
    String name;
    // Constructor - special method called when  you create new instance of this class.  This one takes one parameter called string
    Person(String name) {
        // take parameter and save it
        this.name = name;
    }
    // Method
    public void sayHello() {
        System.out.println("I'm " + name);
    }

    // Static method - methods you can call on a class WITHOUT having an instance of it
    public static void wave() {
        System.out.println("Wave");
    }
}
Person person = new Person("Tommy");
person.sayHello();

// Inheritance - take parent class and modify it a little.  Child has access to everything of parent
public class Vehicle {
    public int wheels() {
        return 4;
    }
    public void go() {
        System.out.println("zoom!");
    }
}

public class Motorcyle extends Vehicle {
    @Override
    public int wheels() {
        return 2;
    }
}

// Interface - list of methods that some class HAS to implement
public interface Teacher {
    public void teach();
}

public class CS50Teacher implements Teacher {
    @Override
    public void teach() {
        // code
    }
}

// Packages - way to namespace / organize files
// package edu.harvard.cs50.example;
// Use a package - import
// import java.util.List;