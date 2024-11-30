% Başar Temiz
% 2022400132
% compiling: yes
% complete: yes



:- ['cmpefarm.pro'].
:- init_from_map.


% 1- agents_distance(+Agent1, +Agent2, -Distance)

%state(Agents,_,_,_) , agents_distance(Agents.0, Agents.1, Distance).

agents_distance(Agent1,Agent2,Distance):-
    get_dict(x,Agent1,ValueX),get_dict(y,Agent1,ValueY),
    get_dict(x,Agent2,ValueX1),get_dict(y,Agent2,ValueY1),
    sub_integer(ValueX,ValueX1,New_x),sub_integer(ValueY,ValueY1,New_y),
    abs(New_x,V_x),abs(New_y,V_y),
    add_integer(V_x,V_y,Distance).
    
    

% 2- number_of_agents(+State, -NumberOfAgents)

% state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], number_of_agents(State, NumberOfAgents).
number_of_agents([Head|_],NumberOfAgents):- 
    dict_length(Head,NumberOfAgents).




% 3- value_of_farm(+State, -Value)
% state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], value_of_farm(State, Value).

value_of_farm(State,Value):-
    get_element(State,0,Agents), % get Agents
    get_element(State,1,Objects), % get Objects
    get_dict_val(Agents,Sum1), get_dict_val(Objects,Sum2), %get the values of the agents and objects
    add_integer(Sum1,Sum2,Value).



get_dict_val(Dict,Value):-
    dict_keys(Dict,Keys), %get keys of the dict
    sum_dict(Dict,Keys,Value).


sum_dict(Dict,[],0).

sum_dict(Dict,[Head|Tail],Sum):-  % a rule for summing the values of the given dict
    get_dict(Head,Dict,Agent),
    get_value(Agent.subtype,Value),
    sum_dict(Dict,Tail,D1),
    Sum is D1+Value.


get_value(wolf,0).

get_value(Type,Value):- % costum rule for adding wolf to the get_value database
    value(Type,Value).

% 4- find_food_coordinates(+State, +AgentId, -Coordinates)

% state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], find_food_coordinates(State, 1, Coordinates).
find_food_coordinates(State,AgentId,Coordinates):-
    get_element(State,0,Agents),
    get_dict(AgentId,Agents,Agent),
    find_coordinates(State,Agent,Coordinates).

find_coordinates(State,Agent,Coordinates):-
    get_element(State,0,Agents),
    dict_keys(Agents,Keys), %get keys of Agents

    (check(Agent,Agents,Keys,Coordinates1)->
    true
    ;
    Coordinates1=[]
    ),

    get_element(State,1,Objects),
    dict_keys(Objects,ObjectK), %get keys of Objects

    (check(Agent,Objects,ObjectK,Coordinates2) ->
    true
    ;
    Coordinates2=[]
    ),

    sum_list(Coordinates1,Coordinates2,Coordinates).
    

check(Agent,Dict,[],[]).

check(Agent,Dict,[Key|Key_rest],[Coor1|Tail1]):-
    get_dict(Key,Dict,Value),
    (
    can_eat(Agent.subtype,Value.subtype) ->
    X is Value.x, Y is Value.y,
    Coor1=[X,Y],
    check(Agent,Dict,Key_rest,Tail1)
    ;
    check(Agent,Dict,Key_rest,[Coor1|Tail1])
    ).
    



        
    




% 5- find_nearest_agent(+State, +AgentId, -Coordinates, -NearestAgent)

%  state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder],find_nearest_agent(State, 0, Coordinates, NearestAgent).

find_nearest_agent(State,AgentId,Coordinates,NearestAgent):-
    
    % we should check all the Agents 
    get_element(State,0,Agents),
    get_dict(AgentId,Agents,Agent),dict_keys(Agents,Keys),
    check_agents(Agents,Keys,Agent,Distances,Oagents),
    lowest_member(N,Distances,Distances,Lowest),
    find_index(Distances,N,Index),
    get_element(Oagents,Index,Oagent),
    Coordinates=[Oagent.x,Oagent.y],
    NearestAgent=Oagent.

check_agents(Agents,[],Agent,[],[]).
check_agents(Agents,[Key|Key_rest],Agent,[Distance1|Distance_rest],[Agent1|Agent_rest]):-
    get_dict(Key,Agents,Oagent),
    agents_distance(Agent,Oagent,Distance),
    Distance1=Distance,
    Agent1=Oagent,
    check_agents(Agents,Key_rest,Agent,Distance_rest,Agent_rest).


    

% 6- find_nearest_food(+State, +AgentId, -Coordinates, -FoodType, -Distance)

% state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], find_nearest_food(State, 1, Coordinates, FoodType, Distance).
find_nearest_food(State,AgentId,Coordinates,FoodType,Distance):-
    get_element(State,0,Agents),
    get_dict(AgentId,Agents,Agent),
    (Agent.subtype\=wolf->
    get_element(State,1,Objects), dict_keys(Objects,Keys),
    check_objects(Objects,Keys,Agent,Distances,Oobjects),
    lowest_member(N,Distances,Distances,Lowest),
    find_index(Distances,N,Index),
    get_element(Oobjects,Index,Oobject),
    Coordinates=[Oobject.x,Oobject.y],
    FoodType=Oobject.subtype,
    Distance=N
    ;
    get_element(State,0,Agents), dict_keys(Agents,Keys),
    check_wolf(Agents,Keys,Agent,Distances,Oagents),
    lowest_member(N,Distances,Distances,Lowest),
    find_index(Distances,N,Index),
    get_element(Oagents,Index,Oagent),
    Coordinates=[Oagent.x,Oagent.y],
    FoodType=Oagent.subtype,
    Distance=N
    ).
    

check_objects(Agents,[],Agent,[],[]).
check_objects(Objects,[Key|Key_rest],Agent,Distances_all,Objects_all):-
    get_dict(Key,Objects,Oobject),
    agents_distance(Agent,Oobject,Distance),
    (can_eat(Agent.subtype,Oobject.subtype)->
    Distances_all=[Distance1|Distance_rest],
    Objects_all=[Oobject1|Object_rest],
    Distance1=Distance,
    Oobject1=Oobject,
    check_objects(Objects,Key_rest,Agent,Distance_rest,Object_rest)
    ;
    check_objects(Objects,Key_rest,Agent,Distances_all,Objects_all)
    ).

check_wolf(Agents,[],Agent,[],[]).
check_wolf(Agents,[Key|Key_rest],Agent,Distances_all,Agents_all):-
    get_dict(Key,Agents,Oagent),
    agents_distance(Agent,Oagent,Distance),
    (can_eat(wolf,Oagent.subtype)->
    Distances_all=[Distance1|Distance_rest],
    Agents_all=[Agent1|Agent_rest],
    Distance1=Distance,
    Agent1=Oagent,
    check_wolf(Agents,Key_rest,Agent,Distance_rest,Agent_rest)
    ;
    check_wolf(Agents,Key_rest,Agent,Distances_all,Agents_all)
    ).

    



% 7- move_to_coordinate(+State, +AgentId, +X, +Y, -ActionList, +DepthLimit)

% state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], move_to_coordinate(State, 0, 2, 5, ActionList, 8).
move_to_coordinate(State,AgentId,X,Y,ActionList,DepthLimit):-
move_to_coordinate_helper(State,AgentId,X,Y,ActionList,DepthLimit,NewState).

move_to_coordinate_helper(State,AgentId,X,Y,ActionList,DepthLimit,NewState):-
    get_element(State,0,Agents),
    get_dict(AgentId,Agents,Agent),
    (Agent.subtype=wolf->
        move_wolf(State,AgentId,Agents,X,Y,DepthLimit,Cur,ActionList,NewState)
        ;
        true
    ),
    (Agent.subtype=cow->
    move_cow(State,AgentId,Agents,X,Y,DepthLimit,Cur,ActionList,NewState)
    ;
    true
    ),
    (Agent.subtype=chicken->
    move_chicken(State,AgentId,Agents,X,Y,DepthLimit,Cur,ActionList,NewState)
    ;
    true
    ).

move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,Action,NewState1):-
    get_element(State,0,Agents1),
    get_dict(AgentId,Agents1,Agent),
    
    Agent.x=X,
    Agent.y=Y,
    NewState1=State,
    Action=[].

move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_down,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_down.
    

move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_down_left,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_down_left.
    

move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_down_right,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_down_right.
   

move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_up,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_up.
   
    
move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_up_left,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_up_left.
   
move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_up_right,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_up_right.
    
move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_right,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_right.
   

move_wolf(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_left,NewState),
    move_wolf(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_left.


% predicates for the chicken

move_chicken(State,AgentId,Agents,X,Y,Depth,Cur,Action,NewState1):-
    get_element(State,0,Agents1),
    get_dict(AgentId,Agents1,Agent),
    
    Agent.x=X,
    Agent.y=Y,
    NewState1=State,
    Action=[].

move_chicken(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_down_left,NewState),
    move_chicken(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_down_left.

move_chicken(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_down_right,NewState),
    move_chicken(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_down_right.

move_chicken(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_up_left,NewState),
    move_chicken(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_up_left.

move_chicken(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_up_right,NewState),
    move_chicken(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_up_right.

% predicates for cow

move_cow(State,AgentId,Agents,X,Y,Depth,Cur,Action,NewState1):-
    get_element(State,0,Agents1),
    get_dict(AgentId,Agents1,Agent),
    
    Agent.x=X,
    Agent.y=Y,
    NewState1=State,
    Action=[].


move_cow(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_down,NewState),
    move_cow(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_down.

move_cow(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_up,NewState),
    move_cow(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_up.

move_cow(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_right,NewState),
    move_cow(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_right.

move_cow(State,AgentId,Agents,X,Y,Depth,Cur,[Action|Rest],NewState1):-
    Depth1 is Depth-1,
    Depth>0,
    move(State,AgentId,move_left,NewState),
    move_cow(NewState,AgentId,Agents,X,Y,Depth1,Cur1,Rest,NewState1),
    Action=move_left.

% 8- move_to_nearest_food(+State, +AgentId, -ActionList, +DepthLimit)
 
% state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], move_to_nearest_food(State, 0, ActionList, 5).
move_to_nearest_food(State,AgentId,ActionList,DepthLimit):-
    find_nearest_food(State,AgentId,Coordinates,FoodType,Distance),
    get_element(Coordinates,0,X),get_element(Coordinates,1,Y),
    move_to_coordinate(State,AgentId,X,Y,ActionList,DepthLimit).



% 9- consume_all(+State, +AgentId, -NumberOfMoves, -Value, NumberOfChildren)

%  state(Agents, Objects, Time, TurnOrder), State=[Agents, Objects, Time, TurnOrder], consume_all(State, 0, NumberOfMovements, Value, NumberOfChildren,).
consume_all(State,AgentId,NumberOfMoves,Value,NumberOfChildren,DepthLimit):-
    iterate_foods(State,AgentId,Moves,0,LastState,DepthLimit),
    (is_there_food(LastState,AgentId)->
    Next_depth is DepthLimit-Moves,
    consume_all(LastState,AgentId,NewMoves,Value,NumberOfChildren,Next_depth),
    NumberOfMoves is Moves+NewMoves
    ;
    get_element(LastState,0,Agents),
    get_dict(AgentId,Agents,Agent),
    NumberOfChildren=Agent.children,
    Value=Agent.energy_point,
    NumberOfMoves=Moves
    ).




find_food_eat(State,AgentId,Moves,DepthLimit,LastState):-
    find_nearest_food(State,AgentId,Coordinates,FoodType,Distance),
    get_element(Coordinates,0,X),get_element(Coordinates,1,Y),
    move_to_coordinate_helper(State,AgentId,X,Y,ActionList,DepthLimit,NewState),
    eat(NewState,AgentId,LastState),
    Moves=DepthLimit.

iterate_foods(State,AgentId,Moves,DepthLimit,LastState,OrLimit):-
    (find_food_eat(State,AgentId,Moves,DepthLimit,LastState)->
    true
    ;
    D1 is DepthLimit+1,
    D1 =< OrLimit,
    iterate_foods(State,AgentId,Moves,D1,LastState,OrLimit)
    ).


% a function to check if there is food
is_there_food(State,AgentId):-
    get_element(State,0,Agents),
    get_dict(AgentId,Agents,Agent),
    (Agent.subtype=wolf->
    dict_keys(Agents,Keys),
    wolf_foods(Agent,Agents,Keys)
    ;
    get_element(State,1,Objects),
    dict_keys(Objects,Keys),
    other_foods(Agent,Objects,Keys)   
    ).

wolf_foods(Agent,Agents,[]):-fail.
wolf_foods(Agent,Agents,[Key|Key_rest]):-
    get_dict(Key,Agents,O_agent),
    (can_eat(wolf,O_agent.subtype)->
    true;
    wolf_foods(Agent,Agents,Key_rest)
    ).
other_foods(Agent,Agents,[]):-fail.
other_foods(Agent,Objects,[Key|Key_rest]):-
    get_dict(Key,Objects,O_object),
    (can_eat(Agent.subtype,O_object.subtype)->
    true;
    other_foods(Agent,Objects,Key_rest)
    ).  

%general functions



square_integer(N,Result):-
    Result is N*N.

add_integer(A,B,Result):-
    Result is A+B.

sub_integer(A,B,Result):-
    Result is A-B.


lenList([],0).

lenList([_|Tail],Len):-
    lenList(Tail,D1),
    Len is D1+1.



dict_length(Dict, Length) :-
    dict_keys(Dict, Keys),
    length(Keys, Length).

get_element([Head|_],0,Head).

get_element([_|Tail],N,Element):-
    D1 is N-1,
    get_element(Tail,D1,Element).

sum_list([],List,List).
sum_list([Head1|Tail1],List2,[Head1|Tail3]):-
    sum_list(Tail1,List2,Tail3).

% a predicate for finding index of a function
find_index([Head|_],Head,0).
find_index([Head|Tail],N,Index):-
    find_index(Tail,N,D1),
    Index is D1+1.
    
lowest_member(N,[],List,N).

lowest_member(N,[Head|Tail],OrList,Lowest):-
    member(Lowest,OrList),
    Lowest=\=0,
    Lowest=<Head,!,
    lowest_member(N,Tail,OrList,Lowest).


lowest_member(N,[Head|Tail],OrList,Lowest):-
    Head=\=0,
    member(Lowest,OrList),!,
    lowest_member(N,Tail,OrList,Head).

lowest_member(N,[Head|Tail],OrList,Lowest):-
    lowest_member(N,Tail,OrList,Lowest).
    
