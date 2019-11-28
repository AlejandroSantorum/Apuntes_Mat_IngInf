%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Authors:
%       · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
%       · Sergio Galán Martín - sergio.galanm@estudiante.uam.es
%   File: assignment3.pl
%   Date: Apr. 3, 2019
%   Version: 1.0
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
duplica([],[]). % base case

duplica([X|L], [X, X|L1]) :- % first element of L is equal to the first
    duplica(L,L1).           % and second elements of L1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
concatena([], L, L). % base case

concatena([X|L1], L2, [X|L3]) :- % elements of first lists goes first
    concatena(L1, L2, L3).       % in the concatenated list


%invierte([],Z,Z) :- !. % base case

%invierte([H|T],Z,Acc) :-    % Inserting first element of the first list
%    invierte(T,Z,[H|Acc]).  % at the beginning of the auxiliary list

%invierte(L1, L2) :-         % Interface for invierte/3
%    invierte(L1, L2, []).

% Auxiliary function
last_and_rest([X],X, []).
% It is supposed to return the entire list but the last element
last_and_rest([A|Xs],E, [A|L]) :-
    last_and_rest(Xs, E, L).

invierte([],[]). % base case

invierte([X], [X]):-!. % base case

invierte([X|R], L) :-
    last_and_rest(L, X, Rest), % checking that X is the last element of
    invierte(R, Rest),!.       % the reversed list
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
palindromo(L) :-
    invierte(L,L).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
divide(L, 0, [], L). % base case, L1 is empty, so the rest of the
                     % elements belogs to L2

divide([F|R1],N,[F|R2],L) :- % iterating over first N elements of L
    divide(R1, M, R2, L),    % inserting those N elems into L1
    N is M+1.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 5
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
aplasta(L, Ret) :-          % interface for aplasta/3
    aplasta(L, [], Ret),!.

aplasta([], Ret, Ret).      % base case

aplasta([F|R], Aux, Ret) :-
    is_list(F),             % case in which first(L) is a list
    !,
    aplasta(F, Ret2),
    concatena(Aux, Ret2, Concat), % concatenating flatten list with the list got before
    aplasta(R, Concat, Ret).

aplasta([F|R], Aux, Ret) :-   % case in which first(L) is not a list
    concatena(Aux, [F], Concat),
    aplasta(R, Concat, Ret).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 6
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
next_factor(N, F, NF) :- % getting possible next factor
    F is 2,
    NF is 3;
    F =< N, % we had to fix it from documentation
    NF is F+2,
    1 is mod(F,2).

primos(1,[],_,_). % base case

primos(N, [NF|R], F, Init) :-
    next_factor(Init, F, NF), % Initializing factor list if not instanciated
    primos(N, [NF|R], NF, Init).

primos(N, L, F, Init) :-
    next_factor(Init, F, NF), % F does not divide N
    primos(N, L, NF, Init).

primos(N, [F|R], F, Init) :-
    0 is mod(N,F),  % case in which F divides N
    X is div(N,F),
    primos(X, R, F, Init).

primos(N, L) :- primos(N, L, 2, N), !. % interface for primos/4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 7
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cod_primero(X,[],[],[X]).

cod_primero(X,[Y|R],[Y|R],[X]) :-
    not(X is Y).

cod_primero(X,[X|R],LRem,[X|R2]) :-
    cod_primero(X,R,LRem,R2).


cod_all([F|R],[E]) :-
    cod_primero(F,R,[],E).

cod_all([F1|R1],[F2|R2]) :-
    cod_primero(F1,R1,Aux,F2),
    cod_all(Aux,R2).


is_coded([],[0,_]).

is_coded([F1|R1],[F2,F1]) :-
    is_coded(R1,[F3,F1]),
    F2 is F3+1.


format_list([],[]).

format_list([F1|R1],[F2|R2]) :-
    is_coded(F1,F2),
    format_list(R1,R2).

run_length(L,L1) :-
    cod_all(L,Aux),
    format_list(Aux,L1).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EXERCISE 8
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
parse(X-Y, X, Y). % parsing element with the form of [a-b] as a and b separately

build_tree([], X) :- % base case: empty list of elements
    X = tree(nil,nil,nil),!.
build_tree([A], X) :- % base case: list with a single element
    parse(A, A1, _),
    X = tree(A1,nil,nil),!.
build_tree([F|R], X) :-
    parse(F, F1, _), % parsing element
    build_tree(R,Z), % calling recursively to keep building the tree
    X = tree(1, tree(F1,nil,nil), Z). % building the tree


% Encodes an element
encode_elem(X1,[F],T) :- % base case
    T = tree(_, L, _),
    L = tree(X1,_,_),    % element is found at the left tree
    F is 0,!.            % the list must contain a 0
encode_elem(X1,[F],T) :- % base case
    T = tree(_, _, R),
    R = tree(X1,_,_),    % element is found at the last right tree
    F is 1,!.
encode_elem(X1,[1|Rest],T) :-
    T = tree(_, _, R),
    encode_elem(X1,Rest,R). % the element is not at the left tree, nor the right
                            % keep recursively

% Encodes a whole list
encode_list([],[],_). % base case
encode_list([Fc|Rc],[Fk|Rk],T) :-
    encode_elem(Fc,Fk,T), % using last predicate as auxiliary
    encode_list(Rc,Rk,T). % carry on recursively



% Calculates the frequency of a given element in a given list
freq_elem(Elem, List, Freq) :-
    freq_elem(Elem, List, Freq, Freq),!.
freq_elem(_, [], _, 0).
freq_elem(Elem, [Elem|R], Freq, Actual) :-
    freq_elem(Elem, R, Freq, Next),
    Actual is Next+1.
freq_elem(Elem, [_|R], Freq, Actual) :-
    freq_elem(Elem, R, Freq, Actual).

% Calculates the frequency of the elements of a given list
frequencies([],_,[]).
frequencies([Elem|Rest], L, [LFf|LFr]) :-
    parse(LFf, Elem, Freq),
    freq_elem(Elem, L, Freq),
    frequencies(Rest,L,LFr).

% Checking a given element is allowed comparing it with the allowed symbols list
elem_belong(Elem, [Elem|_]).
elem_belong(Elem, [_|Ss]) :-
    elem_belong(Elem,Ss).

% Checking all the expression's symbols are allowed
belong([],_).
belong([Elem|Ls],Symbols) :-
	elem_belong(Elem,Symbols),
	belong(Ls,Symbols).

% Calculates the maximum element of a list
list_max([L|Ls],Max) :-
    list_max(Ls,L,Max),!.
list_max([],Max,Max).
list_max([L|Ls],Max0,Max) :-
    parse(Max0,_,MaxNum1),
    parse(L,_,MaxNum2),
    MaxNum1 is max(MaxNum1,MaxNum2),
    list_max(Ls,Max0,Max).
list_max([L|Ls],Max0,Max) :-
    parse(Max0,_,MaxNum1),
    parse(L,_,MaxNum2),
    MaxNum2 is max(MaxNum1,MaxNum2),
    list_max(Ls,L,Max).

% Deletes a given element of a list
delete_letter(_,[],[]).
delete_letter(Let,[Let|R],R):-!.
delete_letter(Let,[F|R],[F|Result]) :-
    delete_letter(Let,R,Result).

% Calculates and deletes the maximum of a list
maximum(Ls,A,Ys) :-
    list_max(Ls,A),
    delete_letter(A,Ls,Ys).

% Sorts the given list by frequency
freq_sort([],[]).
freq_sort(L,[M|Rs]) :-
    maximum(L,M,Rest),freq_sort(Rest,Rs).

% Dictionary for this assignment
dictionary([a,b,c,d,e,f,g,h,i,j,k,l,m,
            n,o,p,q,r,s,t,u,v,w,x,y,z]).

encode(L,X) :-
    dictionary(Allowed_symbols), % Creating dictionary of allowed symbols
    invierte(Allowed_symbols, Symbols), % Inverting symbols
    belong(L,Symbols), % Checking all the expression list's symbols are allowed
    frequencies(Symbols,L,LF), % Calculating frequencies of each symbol
    freq_sort(LF,SL), % Sorting symbols by frequency
    build_tree(SL,T), % Building the tree
    encode_list(L,X,T). % Encoding the expression
