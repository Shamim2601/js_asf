<div align="center">

![Lab Title](assets/logo.svg)

![Estimated completion time](https://img.shields.io/badge/Estimated%20Time-1%20hour-7FFF7F)
&nbsp;
![Overall Difficulty](https://img.shields.io/badge/Overall%20Difficulty-⭐-3498DB)
&nbsp;
![Code Assessed](https://img.shields.io/badge/Code%20Assessed-yes-darkgreen)
&nbsp;
![Eslint Assessed](https://img.shields.io/badge/Style%20Assessed-no-FFC0CB)
&nbsp;
![Test Quality Assessed](https://img.shields.io/badge/Test%20Quality%20Assessed-no-FEDC56)
&nbsp;

---

</div>

*Note*: Week 1 labs are worth 0% of your final grade. However, we will still automark this lab for you and provide you with a score out of 1 to give you a feel of the process. Please see our guide on the Course Website for further details.

[TOC]

# Due Date

Week 2 Monday 6:00 pm [Sydney Local Time](https://www.timeanddate.com/worldclock/australia/sydney)

# Background

## Rationale

Objects are extremely important in JavaScript - they can be used to hold a collection of data, methods, other objects, and so much more!

In this lab, we will explore the tip of the iceberg for what objects can do!

## Setup

- If you are working on a CSE machine (e.g. via VLAB), ensure that you've run the command 1531 setup. You only need to do this once at the beginning of the course.
- Please make sure you have completed both lab01_git and lab01_leap prior.
- Copy the SSH clone link from Gitlab and clone this repository on either VLAB or your local machine.
- In your terminal, change your directory (using the cd command) to the newly cloned lab. To check if you have done this correctly, type ls in this new directory to see if you can see the relevant files (including [objects.js](objects.js)).

## Interface: Functions

An *interface* describes the characteristics of functions without concern for how they are implemented.

Below is an interface for the functions inside [objects.js](objects.js). Each function has:
 * A function name in the source code
 * A list of parameters that they take in
 * A return value/object
 * Specific behaviour in cases where invalid input is provided

<table>
  <tr>
    <th>Name & Description</th>
    <th>Parameters</th>
    <th>Return Type</th>
    <th>Errors</th>
  </tr>
  <tr>
    <td>
        <code>profileCreate</code><br /><br />
         Create a person's profile for the current time.<br/>
         There should be exactly three properties: name, age and createdAt.
         <br/> <br/>
         The updatedAt property should not be in the returned object.
         <br/> <br/>
         Age is calculated by subtracting the birthYear from the currentYear.<br/>
         You do not need to worry about invalid inputs for birthYear, negative age, months of the year, etc.
         <br/> <br/>
         Below is a sample return value:
<pre>{
  name: 'Feliks Zemdegs,
  age: 28,
  createdAt: 1715151808,
}</pre>
        <br/><br/><b>Difficulty</b>: ⭐⭐
    </td>
    <td>
        <code>(nameFirst, nameLast, birthYear)</code>
    </td>
    <td>
        <code>PersonProfile</code>
    </td>
    <td>
        N/A
    </td>
  </tr>
  <tr>
    <td>
        <code>profileCompareAge</code><br /><br />
        Compare the age of two different profiles.
        <ul>
        <li>If profile1's age is higher than profile2's age, return any positive number (e.g. 1)</li>
        <li>If profile1's age is less than profile2's age, return any negative number (e.g. -1)</li>
        <li>Otherwise, profile1's age is the same as profile2's age, return 0.</li>
        </ul>
        <br/><br/><b>Difficulty</b>: ⭐
    </td>
    <td>
        <code>(profile1, profile2)</code>
    </td>
    <td>
        <code>number</code>
    </td>
    <td>
        N/A
    </td>
  </tr>
  <tr>
    <td>
        <code>profileUpdateName</code><br /><br />
<p>Given a profile,</p>
<ol>
  <li>Edit the profile's name to be the new name</li>
  <li>Create (if not exist) or edit the property updatedAt
</ol>
<p>For example, if the given profile is:</p>
<pre>
{
  name: 'Alan Becker',
  age: 34,
  createdAt: 1715153483
}
</pre>
<p>and we make a function call such as: <code>profileUpdateName('The Chosen One')</code></p>
<p>The new object could look like:</p>
<pre>{
  name: 'The Chosen One',
  age: 34,
  createdAt: 1715153483
  updatedAt: 1715153612
}</pre>
<p>
  where updatedAt would depend on the current time.
  <br/> <br/>
  You do NOT need to worry about the age field
  <br/> <br/>
  You do NOT need to return anything in this function.
  <br/>
  (i.e. the return type is undefined - you should not use the return keyword)
</p>
        <br/><br/><b>Difficulty</b>: ⭐
    </td>
    <td>
        <code>(profile)</code>
    </td>
    <td>
        <code>undefined</code>
        <br/>
        (this means that you do not need to return anything)
    </td>
    <td>
        N/A
    </td>
  </tr>
  <tr>
    <td>
        <code>profileHasUpdate</code><br /><br />
       Returns
       <ul>
         <li>true if the profile has the property 'updatedAt'
         <li>false otherwise</li>
       </ul>
       <br/>
      <b>Difficulty</b>: ⭐
    </td>
    <td>
        <code>(profile)</code>
    </td>
    <td>
        <code>boolean</code>
    </td>
    <td>
        N/A
    </td>
   <tr>
    <td>
        <code>profileSerialise</code><br /><br />
       Returns a JSON serialised string for a profile object.
       <br/>
       Hint: try searching online for a built-in JavaScript function
       <br/>
       <br/>
      <b>Difficulty</b>: ⭐
    </td>
    <td>
        <code>(profile)</code>
    </td>
    <td>
        <code>string</code>
    </td>
    <td>
        N/A
    </td>
  </tr>
   <tr>
    <td>
        <code>profileDeserialise</code><br /><br />
       Returns the original object after deserialising the JSON string for a profile object.
       <br/>
       Hint: try searching online for a built-in JavaScript function
       <br/>
       <br/>
      <b>Difficulty</b>: ⭐
    </td>
    <td>
        <code>(profile)</code>
    </td>
    <td>
        <code>string</code>
    </td>
    <td>
        N/A
    </td>
  </tr>
</table>

## Interface: Data Types

This is the type definition for the input/output of the functions in the [Interface: Functions](#interface-functions).

For this lab, we will define a template for the object PersonProfile as:
ts
{
  name: string,         // e.g. 'Feliks Zemdegs'
  age: string,          // e.g. 28
  createdAt: number,    // e.g. 1715151808

  // NOTE: this field is OPTIONAL, meaning it may or may not exist in the object.
  // This is denoted by the question mark (?)
  updatedAt?: number    // e.g. 1715151808
}


| If a variable...                               | It is of type...                                           |
|------------------------------------------------|-------------------------------------------------------------|
| is exactly or starts with the prefix *name* | string                                       |
| is exactly *birthYear*                       | number, specifically integer                |
| is exactly *age*                             | number, specifically integer                |
| is exactly *createdAt*                       | number, specifically an [integer UNIX timestamp](https://flaviocopes.com/how-to-get-timestamp-javascript) in seconds (not milliseconds!) |
| is exactly *updatedAt*                       | number, specifically an [integer UNIX timestamp](https://flaviocopes.com/how-to-get-timestamp-javascript) in seconds (not milliseconds!) |
| is exactly or starts with the prefix *profile*| PersonProfile                         |

# Task

Your task is to *implement the functions in [Interface](#interface-functions)*.

## Implementation

Open the file [objects.js](./objects.js) in your preferred text editor. The stub code (interface with a fake temporary implementation) for each function has been provided for you.

Before replacing them with your implementation, pay close attention to the returned object and see how it aligns with the [Interface: Functions](#interface-fuctions) and [Interface: Data Types](#interface-data-types).

Complete all listed functions.

## Run & Test

You can run and test your code by typing the following in a terminal that is opened at the directory (folder) for this lab:
shell
$ node objects.js

This executes the code in [objects.js](objects.js), including the console.log at the bottom of the file.

## Output format of console.log

When debugging your code, you may find that the output of console.log has:
- different colours (e.g. yellow/brown for numbers)
- different spacing (e.g. spaces between brackets)
- new lines (e.g. after an opening bracket)
- other slight differences in indentation, commas, etc

This is completely fine. What matters is the returned value of your functions, which is what we will be assessing you on.

Using console.log is strictly for debugging purposes. It will not affect your mark in any way. In other words, how your results are displayed when printed or whether you leave these console.log statements in your code has 0 effects on your final automarking result.

### Tips for Printing Objects

For objects with deeply-nested structures, sometimes they may show up when printed with console.log as [Object] or [Array]. In this case, what you can do is convert them to a JSON string before printing, e.g.
javascript
// rather than:
console.log(yourDeeplyNestedObject);

// we can do:
console.log(JSON.stringify(yourDeeplyNestedObject, null, 2));

The third argument, "2", will pretty-print your object with 2 space indentation. You can view the documentation for JSON.stringify [here](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/stringify).

# Submission

- Use git to add, commit, and push your changes on your master branch.
- Check that your code has been uploaded to your Gitlab repository on this website (you may need to refresh the page).

*If you have pushed your latest changes to master on Gitlab no further action is required! At the due date and time, we automatically collect your work from what's on your master branch on Gitlab.*

# Notes
- We will only test the behaviour explicitly defined in the specification. For cases that are not covered, you can make assumptions about how the relevant functions should behave.
- Passing the given tests is a good indication of correctness but does not guarantee that you will receive the full mark for the lab.
- You are advised to do further testing. In this lab, this can be done by adding more console.log at the bottom of [objects.js](objects.js)
- You are not allowed to use any external libraries/modules in this exercise. This simply means that your code should run on a CSE machine without needing to use the npm install command
