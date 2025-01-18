# Ranked-Choice-Voting-System
A program that conducts an election based on the ranked choice method. Votes can be of any generic type.

## Vote
A vote here is an object that contains the choice (of any generic type) and the rank assigned to it by the voter.
A voter necessarily has as many votes as there are choices.

## Result
This is an object that contains the choice, the number of votes it recieved, and the percentage of votes it recieved

## Votes 
Votes here is an object that contains all the votes for a user. Each voter has a votes object associated to it.

## Election
This is the object that contains all the 'votes' objects corresponding to the voters in the election.

The calculateResults() method has a results vector (each element being a result object) in which it stores the results for the election.
For each choice, the method first checks for votes where the choice has been ranked first. If one choice has more than 50% of the votes, we have a winner.
or if there are only 2 choices, and both have 50% vote share, we have a tie.

if all choices have less than 50% of the vote share, the choice with the lowest vote share is removed and then we find the second choice of all the voters 
who ranked that choice first. These votes are then distributed to the remaining choices.

if all choices have the same vote share and that number is less than 50%, the first choice is removed and we proceed as discussed above.

The method then checks if any one choice has acquired a vote share greater than 50%, if yes, we have a winner. If not, we continue till we either have a winner or have a tie (which occurs when there are only 2 remaining choices each with 50% of the vote share).