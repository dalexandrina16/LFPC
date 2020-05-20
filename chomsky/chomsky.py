from string import letters
import copy
import re

def large(rules,let,voc):

    new_dict = copy.deepcopy(rules)
    for key in new_dict:
        values = new_dict[key]
        for i in range(len(values)):
            if len(values[i]) > 2:

                for j in range(0, len(values[i]) - 2):
                    if j==0:
                        rules[key][i] = rules[key][i][0] + let[0]
                    else:
                        rules.setdefault(new_key, []).append(values[i][j] + let[0])
                    voc.append(let[0])
                    new_key = copy.deepcopy(let[0])
                    let.remove(let[0])
                rules.setdefault(new_key, []).append(values[i][-2:])

    return rules,let,voc


def empty(rules,voc):

    e_list = []

    new_dict = copy.deepcopy(rules)
    for key in new_dict:
        values = new_dict[key]
        for i in range(len(values)):
            if values[i] == 'e' and key not in e_list:
                e_list.append(key)
                rules[key].remove(values[i])
        if len(rules[key]) == 0:
            if key not in rules:
                voc.remove(key)
            rules.pop(key, None)

    new_dict = copy.deepcopy(rules)
    for key in new_dict:
        values = new_dict[key]
        for i in range(len(values)):
            if len(values[i]) == 2:
                if values[i][0] in e_list and key!=values[i][1]:
                    rules.setdefault(key, []).append(values[i][1])
                if values[i][1] in e_list and key!=values[i][0]:
                    if values[i][0]!=values[i][1]:
                        rules.setdefault(key, []).append(values[i][0])

    return rules,voc

def short(rules,voc):
    D = dict(zip(voc, voc))
    for key in D:
        D[key] = list(D[key])
    for letter in voc:
        for key in rules:
            if key in D[letter]:
                values = rules[key]
                for i in range(len(values)):
                    if len(values[i]) == 1 and values[i] not in D[letter]:
                        D.setdefault(letter, []).append(values[i])

    rules,D = short1(rules,D)
    return rules,D


def short1(rules,D):
    new_dict = copy.deepcopy(rules)
    for key in new_dict:
        values = new_dict[key]
        for i in range(len(values)):
            if len(values[i]) == 1:
                rules[key].remove(values[i])
        if len(rules[key]) == 0: rules.pop(key, None)
    for key in rules:
        values = rules[key]
        for i in range(len(values)):
            for j in D[values[i][0]]:
                for k in D[values[i][1]]:
                    if j+k not in values:
                        rules.setdefault(key, []).append(j + k)

    return rules,D


def final_rules(rules,D,S):

    for let in D[S]:
        if not rules[S] and not rules[let]:
            for v in rules[let]:
                if v not in rules[S]:
                    rules.setdefault(S, []).append(v)
    return rules

def print_rules(rules):
    for key in rules:
        values = rules[key]
        for i in range(len(values)):
            print key + '->' + values[i]
    return 1


def main():

    rules = {}
    voc = []
    let = list(letters[26:]) + list(letters[:25])

    let.remove('e')

    while True:
        userInput = raw_input('Give number of rules')
        try:
            N = int(userInput)
            if N <=2: print 'N must be a number >=2!'
            else: break
        except ValueError:
            print "That's not an int!"

    # Initial state
    while True:
        S = raw_input('Give initial state')
        if not re.match("[a-zA-Z]*$", S): print 'Initial state must be a single \
character!'
        else:break

    print '|Give rules in the form A B (space-delimited), for A->B|'
    print '|or A BCD, if more than one states in the right part   |'
    print '|(without spaces between right part members).          |'
    print '|for epsilon use \'e\'                                 |'

    for i in range(N):
        fr, to = map(str,raw_input('Rule #' + str(i + 1)).split())
        for l in fr:
            if l!='e' and l not in voc: voc.append(l)
            if l in let: let.remove(l)
        for l in to:
            if l!='e' and l not in voc: voc.append(l)
            if l in let: let.remove(l)
        rules.setdefault(fr, []).append(to)

    print '\nRules after large rules removal'
    rules,let,voc = large(rules,let,voc)
    print_rules(rules)

    print '\nRules after empty rules removal'
    rules,voc = empty(rules,voc)
    print_rules(rules)

    print '\nRules after short rules removal'
    rules,D = short(rules,voc)
    print_rules(rules)

    print '\nFinal rules'
    rules = final_rules(rules,D,S)
    print_rules(rules)

if __name__ == '__main__':
    main()
