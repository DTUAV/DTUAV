using System.Collections.Generic;
using System.Security.Cryptography.X509Certificates;
using UnityEngine;
using Random = System.Random;
using DTUAV.Visualization_Module.Line;

namespace DTUAV.Algorithm_Module.Path_Planning.RRT
{
  
    struct TreeNode
    {
        public int parentId;
        public int ownId;
        public Vector2 nodePosition;
    }

    public class RRT2D
    {
        private float _stepDetal; //the step to move
        private long _maxFindStep; //the max step to find the path
        private float _safeRange; //the safe range
        private float _findError;
        private float _rangeProbability;
        private Vector2 _startPosition;
        private Vector2 _targetPosition;
        private Vector2 _workMinRange;
        private Vector2 _workMaxRange;
        private float _height;
        private Random _random;
        private List<Vector2> _path;
        private List<TreeNode> _treeNodes;
        private bool _isFind;
        private EnvironmentalPerception2D _environmentalPerception2D;
        private Line _line;

        public bool SetWorkMaxRange(Vector2 workMaxRange)
        {
            _workMaxRange = workMaxRange;
            return true;
        }

        public bool SetWorkMinRange(Vector2 workMinRange)
        {
            _workMinRange = workMinRange;
            return true;
        }

        public bool SetTargetPosition(Vector2 targetPosition)
        {
            _targetPosition = targetPosition;
            return true;
        }

        public bool SetStartPosition(Vector2 startPosition)
        {
            _startPosition = startPosition;
            return true;
        }

        public bool SetSafeRange(float safeRange)
        {
            _safeRange = safeRange;
            return true;
        }

        public bool SetMaxFindStep(long maxFindStep)
        {
            _maxFindStep = maxFindStep;
            return true;
        }

        public bool SetStepDetal(float stepDetal)
        {
            _stepDetal = stepDetal;
            return true;
        }

        public bool GetIsFind()
        {
            return _isFind;
        }

        public List<Vector2> GetPath()
        {
            return _path;
        }

        public Vector2 GetMaxRange()
        {
            return _workMinRange;
        }

        public Vector2 GetMinRange()
        {
            return _workMaxRange;
        }

        public Vector2 GetTargetPosition()
        {
            return _targetPosition;
        }

        public Vector2 GetStartPosition()
        {
            return _startPosition;
        }

        public float GetMaxFindStep()
        {
            return _maxFindStep;
        }

        public float GetStepDetal()
        {
            return _stepDetal;
        }

        private float randData(float minRange, float maxRange)
        {
            return (float)(_random.NextDouble() * (maxRange - minRange) + minRange);
        }

        [System.Obsolete]
        public bool FindPath()
        {

            TreeNode startNode = new TreeNode();
            startNode.nodePosition = _startPosition;
            startNode.parentId = 0;
            startNode.ownId = 0;
            _treeNodes.Add(startNode);
            Vector2 nextTargetPosition = new Vector2();
            Vector2 tempDir = new Vector2();
            TreeNode tempNode = new TreeNode();
            TreeNode newNode = new TreeNode();
            int j = 1;
            for (int i = 0; i < _maxFindStep; i++)
            {
                if (_random.NextDouble() >= _rangeProbability)
                {
                    nextTargetPosition = _targetPosition;
                }
                else
                {
                    nextTargetPosition = new Vector2(randData(_workMinRange.x, _workMaxRange.x), randData(_workMinRange.y, _workMaxRange.y));
                }
                //Debug.Log(nextTargetPosition);
                tempNode = FindNearNode(nextTargetPosition);
                tempDir.x = (nextTargetPosition.x - tempNode.nodePosition.x) * _stepDetal / Vector2.Distance(nextTargetPosition, tempNode.nodePosition);
                tempDir.y = (nextTargetPosition.y - tempNode.nodePosition.y) * _stepDetal / Vector2.Distance(nextTargetPosition, tempNode.nodePosition);
                newNode.nodePosition = tempNode.nodePosition + tempDir;
                _environmentalPerception2D.UpdateSensor(new Vector3(newNode.nodePosition.x, _height, newNode.nodePosition.y));
                    newNode.ownId = j;
                    newNode.parentId = tempNode.ownId;
                    if (_environmentalPerception2D.GetIsSafe())
                    {
                        _treeNodes.Add(newNode);
                        j = j + 1;
                        _line.SetPosition(new Vector3(tempNode.nodePosition.x, _height, tempNode.nodePosition.y),
                            new Vector3(newNode.nodePosition.x, _height, newNode.nodePosition.y));
                        _line.DrawLine();
                    }

                    if (Vector2.Distance(newNode.nodePosition,_targetPosition)<=_findError)
                    {
                        _isFind = true;
                        break;
                    }
            }


            if (_isFind)
            {
                int parentId = _treeNodes[_treeNodes.Count - 1].parentId;
                List<Vector2> _tempPath = new List<Vector2>();
                _tempPath.Add(_treeNodes[_treeNodes.Count - 1].nodePosition);
                TreeNode tempTreeNode = new TreeNode();
                while (parentId != 0)
                {
                    tempTreeNode = GetParentNode(parentId);
                    parentId = tempTreeNode.parentId;
                    _tempPath.Add(tempTreeNode.nodePosition);
                }
                _tempPath.Add(_startPosition);

                for (int i = _tempPath.Count - 1; i >= 0; i--)
                {
                    _path.Add(_tempPath[i]);
                }
                _line.ClearAllLine();
                Vector2 startPosition = _path[0];
                for (int i = 0; i < _path.Count; i++)
                {
                    _line.SetPosition(new Vector3(startPosition.x, _height, startPosition.y),
                        new Vector3(_path[i].x, _height, _path[i].y));
                    _line.DrawLine();
                    startPosition = _path[i];
                }
                return true;
            }
            else
            {
                return false;
            }

        }
    

    private TreeNode GetParentNode(int ParentID)
        {
            TreeNode retNode = new TreeNode();
            for (int i = 0; i < _treeNodes.Count; i++)
            {
                if (_treeNodes[i].ownId == ParentID)
                {
                    retNode = _treeNodes[i]; 
                }
            }

            return retNode;
        }

        private TreeNode FindNearNode(Vector2 targetPosition)
        {
            TreeNode retNode = new TreeNode();
            float distance = 10000;
            for (int i = 0; i < _treeNodes.Count; i++)
            {
                if (Vector2.Distance(targetPosition,_treeNodes[i].nodePosition)<= distance)
                {
                    retNode = _treeNodes[i];
                    distance = Vector2.Distance(targetPosition, _treeNodes[i].nodePosition);
                }
            }
           // Debug.Log(distance);
            return retNode;
        }

        public bool FindPath(Vector2 startPosition, Vector2 targetPosition)
        {
            _startPosition = startPosition;
            _targetPosition = targetPosition;
            return FindPath();
        }

        public bool InitPlotLine(Material mat, Color color, float widthX, float widthY,
            bool isPlot)
        {
            _line = new Line(mat,color,widthX,widthY, isPlot);
            return true;
        }

        public bool InitSensor(LayerMask layerMask, float minRange, float maxRange, Vector3 currentPosition,
            float horizontalAngleStart, float horizontalAngleEnd, float horizontalAngleInc, float safeRange,
            bool showLidar)
        {
            _environmentalPerception2D = new EnvironmentalPerception2D(layerMask,minRange,maxRange,currentPosition,horizontalAngleStart,horizontalAngleEnd,horizontalAngleInc,safeRange,showLidar);
            return true;
        }

        public RRT2D(float stepDetal,long maxFindStep,Vector2 startPosition,Vector2 targetPosition,Vector2 workMinRange, Vector2 workMaxRange, float safeRange, float findError, float rangeProbability, float height)
        {
            _stepDetal = stepDetal;
            _maxFindStep = maxFindStep;
            _workMinRange = workMinRange;
            _workMaxRange = workMaxRange;
            _startPosition = startPosition;
            _targetPosition = targetPosition;
            _safeRange = safeRange;
            _findError = findError;
            _rangeProbability = rangeProbability;
            _height = height;
            _random = new Random();
            _path = new List<Vector2>();
            _treeNodes = new List<TreeNode>();
        }
    }

}
