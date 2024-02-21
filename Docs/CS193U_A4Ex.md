# BehaviorTree Nodes

## Decorator Nodes

### Notify Observer

Set the notified event when the blackboard key query has changed.

### Observer aborts

When the blackboard key query has changed, it will abort the child node or lower priority nodes.

- None: No observer aborts.
- LowerPriority: Abort the lower priority nodes(left node).
- Self: Abort the child node.
- Both: Abort the lower priority nodes and the child node.

## Service Nodes

Node ticked events. It is used to update the blackboard key value.

## EQS

### Context

## Ref

https://www.bilibili.com/read/cv13400311/

https://docs.unrealengine.com/4.26/en-US/InteractiveExperiences/ArtificialIntelligence/EQS/EQSQuickStart/
