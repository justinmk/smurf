# transition:
#   - moves forward in time
#   - per-user
class Record:
    def __init__(self, ts, userid, pageid):
        self.ts = ts
        self.userid = userid
        self.pageid = pageid

# records is sorted by timestamp.
def count_transitions(records):
    usermap = {}
    transitions = {}
    max = 0
    max_transition_name = ''
    for r in records:
        if r.userid not in usermap:
            usermap[r.userid] = r.pageid
        else:
            prevpageid = usermap[r.userid]
            usermap[r.userid] = r.pageid
            transition = prevpageid + "-" + r.pageid
            if transition not in transitions:
                transitions[transition] = 0
            transitions[transition] += 1
            if max < transitions[transition]:
                max = transitions[transition]
                max_transition_name = transition

    return max, max_transition_name

records = [
    Record(123,  'Bob'  , 'Main'    ),
    Record(234,  'Bob'  , 'Product' ),
    Record(345,  'Sally', 'Main'    ),
    Record(456,  'Bob'  , 'Checkout'),
    Record(567,  'Sally', 'Product' ),
    Record(568,  'Sally', 'Exit' ),
    Record(569,  'Bob', 'Product' ),
    Record(571,  'Sally', 'Product' ),
    Record(571,  'Freb', 'Product' ),
    Record(571,  'Freb', 'Exit' ),
    Record(571,  'Freb', 'Main' ),
    Record(571,  'Freb', 'Product' ),
    Record(569,  'Bob', 'About' ),
    Record(568,  'Sally', 'About' ),
]
print(count_transitions(records))
